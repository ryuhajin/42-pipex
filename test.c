# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

// int main (void)
// {
// 	int fd[2];
// 	pid_t pid;
// 	pid_t pid_2;

// 	if (pipe(fd) == -1)
// 		return 0; //pipe error
// 	pid = fork();
// 	if (pid == -1)
// 		return 0; //fork error; 자식 하나가 오류일 때 부모가 끝나면 정상 fork된 자식은 고아가 되나?
// 	if (pid == 0) // 표준 입력으로 입력 받아 표준 출력(파이프)에 쓰고
// 	{
// 		close(fd[0]); // pipe read close
// 		if (dup2(fd[1], STDOUT_FILENO) == -1) // pipe write -> STDOUT
// 			return 0; // fd error
// 		close(fd[1]);
// 		// printf("hey child 2. I'm child 1.\n");
// 		execve("/bin/cat", (char**){"cat"}, (char**){"/bin"});
// 	}
// 	pid_2 = fork();
// 	if (pid_2 == -1)
// 		return 0;
// 	if (pid_2 == 0) // 표준 입력으로 입력 받아 표준 출력(파이프)에 쓰고
// 	{
// 		close(fd[1]); // pipe write close
// 		if (dup2(fd[0], STDIN_FILENO) == -1) // pipe read -> STDIN
// 			return 0; // fd error
// 		close(fd[0]);
// 		char buff[1024];
// 		read(STDIN_FILENO, buff, 1024);
// 		// printf("child2 : %s", buff);
// 		// execve("/bin/cat", (char**){"cat"}, (char**){"/bin"});
// 		execve("./a.out", (char**){"./a.out"}, (char**){"/bin"});
// 	}
// 	close(fd[0]); // 부모 파이프 닫기
// 	close(fd[1]);

// 	return 0;
// }

// int main (int argc, char * argv[], char ** envp)
// {
// 	int fd[2];
	
// 	if (argc != 5)
// 		return 0;	
// 	if (pipe(fd) == failed)
// 	{	
// 		perror("pipe error");
// 		exit(1); //error exit
// 	}

// 	t_input * node;
// 	make_input_node(&node, argc, argv, envp);
// 	check_handler(node);
// 	cmd_print(node);
// 	path_print(node);
// 	file_path_print(node);

// 	return 0;
// }

int main(void)
{
	int n = 3;
	pid_t pids[n];

	for(int i = 0; i < n; i++){
		if((pids[i] = fork()) == 0){
			printf("Child process pid: %d. Sleep for %d Sec soon.\n", getpid(), 3*(n-i));
			sleep(3*(n-i));
			printf("pid %d woke up!\n", getpid());
			exit(0);
		}
	}
	pid_t p = 0;
	while ((p = waitpid(-1, 0, WNOHANG)) > -1)
	{
		printf("waitpid returned value %d\n", p);
		sleep(1);
	}
}
