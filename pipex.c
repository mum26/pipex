#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	iofds[2];
	int	pipefds[2];
	pid_t	pid;

	iofds[I] = open(argv[2], O_RDONLY);
	iofds[O] = open(argv[argc], O_WRONLY | O_CREAT);

	char *cmd_args1[] = {argv[3], NULL};
	char *cmd_args2[] = {argv[4], NULL};

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
		close(pipefds[R]);
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
		{
			perror("dup2(2)");
			exit(EXIT_FAILURE);
		}
		close(pipefds[W]);

		if (execve(argv[3], cmd_args1, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		close(pipefds[W]);
		if (dup2(pipefds[R], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipefds[R]);

		if (execve(argv[4], cmd_args2, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

