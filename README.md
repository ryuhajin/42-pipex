# pipex · 42 Seoul

> 셸의 `< infile cmd1 | cmd2 > outfile` 동작을 `fork`, `pipe`, `dup2`, `execve`로 직접 재현하는 과제

## 개요
입력 파일과 명령어들을 인자로 받아, 각 명령어를 자식 프로세스로 실행하고 파이프로 연결해 결과를 출력 파일에 쓴다.
mandatory는 명령어 2개, bonus는 명령어 N개(다중 파이프)와 `here_doc`을 지원한다.

## 구현 포인트
- **명령어 경로 탐색**: `search_path_from_env`가 `envp`에서 `PATH=`를 찾아 `:`로 나누고, `finds_cmd_in_env_path`가 각 디렉터리에 명령어 이름을 붙여 `access(F_OK)`로 확인한다. `/`, `./`, `../`로 시작하면(`starts_with_directory`) 경로를 그대로 사용한다.
- **파이프 준비**: `make_pipes`가 `cmd_cnt - 1`개의 파이프를 미리 만들어 `int **pipes`에 저장한다.
- **fork / dup2 흐름**: `make_child`가 명령어마다 `fork`하고, 자식은 `child_pipe_setting`에서 자신과 무관한 파이프를 모두 닫은 뒤(`close_fd`) 위치에 따라 fd를 연결한다.
  - 첫 명령어: `infile` → stdin, `pipes[i]` 쓰기 끝 → stdout (`fd_dup_for_first_cmd`)
  - 중간 명령어: `pipes[i-1]` 읽기 끝 → stdin, `pipes[i]` 쓰기 끝 → stdout (`fd_dup_for_middle_cmd`)
  - 마지막 명령어: `pipes[i-1]` 읽기 끝 → stdin, `outfile` → stdout (`fd_dup_for_last_cmd`)
  - 부모는 `close_fd_all`로 모든 파이프를 닫고 `wait_for_child`로 자식 수만큼 `wait`한다.
- **에러 처리**: 입력/출력 파일과 명령어의 존재·권한을 `access`로 검사해 `No such file or directory`, `Permission denied`, `command not found` 메시지를 stderr로 출력한다(`access.c`). 빈 문자열이나 공백만 있는 인자는 `check_for_argv`에서 거른다.
- **bonus: here_doc**: 첫 인자가 `here_doc`이면 `get_next_line`으로 stdin을 LIMITER가 나올 때까지 읽어 임시 파일에 저장하고(`make_here_doc_file`), 같은 이름의 파일이 있으면 숫자를 붙여 새 이름을 만든다(`make_non_duplicate_name`). 출력 파일은 `O_APPEND`로 열고, 종료 시 임시 파일은 `unlink`한다.

## 빌드 & 실행
```bash
make
./pipex infile "ls -l" "wc -l" outfile
# < infile ls -l | wc -l > outfile 과 동일
```

bonus (같은 이름의 `pipex` 바이너리로 빌드됨)
```bash
make bonus
./pipex infile "cat" "grep a" "sort" "uniq" outfile
./pipex here_doc LIMITER "cat" "wc -l" outfile
# cat << LIMITER | wc -l >> outfile 과 동일
```

## 구조
```
pipex/
├── makefile
├── pipex.h
├── main.c          # 인자 개수 검사, 전체 흐름
├── init.c          # 인자 split, 파이프/노드 할당
├── input.c         # PATH 탐색, 명령어 경로 결정
├── fork.c          # fork, execve, wait
├── pipe.c pipe2.c  # dup2 / close 로 파이프 연결
├── access.c        # 파일·명령어 접근 권한 검사
├── check_argv.c    # 빈 인자 검사, ft_perror
├── free.c
├── bonus/          # *_bonus.c: 다중 파이프, here_doc, get_next_line
└── libft/          # 직접 구현한 libft
```

42 Seoul 공통 과정 과제.
