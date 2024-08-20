//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//
//int	main(void)
//{
//	int	pipefds[2];
//	pid_t	pid;
//
//	char *argv[] = {"/bin/ls", NULL};
//	char *argv2[] = {"/usr/bin/grep", ".txt", NULL};
//	extern char **environ;
//	if (pipe(pipefds) == -1)
//	{
//		perror("pipe(2)");
//		exit(EXIT_FAILURE);
//	}
//
//	pid = fork();
//	if (pid == -1)
//	{
//		perror("fork(2)");
//		exit(EXIT_FAILURE);
//	}
//
//	if (pid == 0)
//	{
//		close(pipefds[0]);
//		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
//		{
//			perror("dup2(2)");
//			exit(EXIT_FAILURE);
//		}
//		close(pipefds[1]);
//
//		if (execve("/bin/ls", argv, environ) == -1)
//		{
//			perror("execve");
//			exit(EXIT_FAILURE);
//		}
//	}
//	else
//	{
//		wait(NULL);
//		close(pipefds[1]);
//		if (dup2(pipefds[0], STDIN_FILENO) == -1)
//		{
//			perror("dup2");
//			exit(EXIT_FAILURE);
//		}
//		close(pipefds[0]);
//
//		if (execve("/usr/bin/grep", argv2, environ) == -1)
//		{
//			perror("execve");
//			exit(EXIT_FAILURE);
//		}
//	}
//	return (0);
//}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int	pipefds[2];
	pid_t	pid;

	char *argv[] = {"/bin/ls", NULL};
	char *argv2[] = {"/usr/bin/grep", "out", NULL};
	extern char **environ;

	if (pipe(pipefds) == -1)
	{
		perror("pipe(2)");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork(2)");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// 子プロセス
		close(pipefds[0]);
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2(2)");
			exit(EXIT_FAILURE);
		}
		close(pipefds[1]);

		// /bin/ls を実行し、出力をファイルにリダイレクト
		FILE *file = fopen("ls_output.txt", "w");
		if (file == NULL) {
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		dup2(fileno(file), STDOUT_FILENO);
		fclose(file);

		if (execve("/bin/ls", argv, environ) == -1)
		{
			perror("execve ls");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		close(pipefds[1]);
		if (dup2(pipefds[0], STDIN_FILENO) == -1)
		{
			perror("dup2(2)");
			exit(EXIT_FAILURE);
		}
		close(pipefds[0]);

		// /usr/bin/grep を実行
		if (execve("/usr/bin/grep", argv2, environ) == -1)
		{
			perror("execve grep");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

