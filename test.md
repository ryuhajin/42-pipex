# 경로
path에 존재 <> 현재경로에 존재, 상대/절대 경로에 존재
1. 기본
- path에만 존재하는 프로그램
	infile cat cat outfile
- 현재경로에만 존재하는 프로그램
	infile mycat mycat outfile (실행되면 안됨)
	infile ./mycat ./mycat outfile
- 상대경로에만 존재하는 프로그램
	infile ./testfolder/mycat ./testfolder/mycat outfile (사실 이건 나도 처음 해봄)
- 절대경로에만 존재하는 프로그램
	infile /mycat /mycat outfile
2. 응용
- path에 존재하고 현재경로에도 존재하는 프로그램
	infile cat cat outfile
3. 번외
	infile testfolder/mycat testfolder/mycat outfile (사실 이건 나도 처음 해봄)

# 파일
+ infile
	1. 기본
		- 존재하는 파일
			infile cat cat outfile
		- 존재하지 않는 파일
			filenotexist cat cat outfile
	2. 응용
		- 읽기 권한이 없는 파일
			testfolder/noread.txt cat cat outfile
			testfolder/writeonly.txt cat cat outfile
			testfolder/executeonly.txt cat cat outfile
		- 읽기는 있지만, 쓰기/실행 권한이 없는 파일 (실행이 되야 함)
			testfolder/readonly.txt cat cat outfile
+ outfile
	1. 기본
		- 존재하는 파일
			infile cat cat outfile
		- 존재하지 않는 파일
			infile cat cat filenotexist
	2. 응용
		- 읽기 권한이 없는 파일
			testfolder/nowrite.txt cat cat outfile
			testfolder/writeonly.txt cat cat outfile
			testfolder/executeonly.txt cat cat outfile
		- 쓰기는 있지만, 읽기/실행 권한이 없는 파일 (실행이 되야 함)
			testfolder/writeonly.txt cat cat outfile

# pipe 확인
yes | head -> y 10번 출력
cat | cat | ls -> ls 출력, 2번 입력받고 끝


프로그램 실행 (init) -> (process) -> (clean)
(초기화)프로그램에 사용되는 메모리를 할당
(프로세싱)처리를 하고
	만약 실패시, 실패처리
(클린)메모리 해제

<처리>
입력부분 파싱
	만약 실패시, 실패처리
실행
	만약 실패시, 실패처리
