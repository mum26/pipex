/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/08/24 23:30:57 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		die("pipe");
	pid = fork();
	if (pid == -1)
		die("fork");

	if (pid == 0)
	{
		close(pipefds[R]);
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup2");
		close(pipefds[W]);

		if (execve(argv[3], cmd_args1, env) == -1)
			die("execve");
	}
	else
	{
		wait(NULL);
		close(pipefds[W]);
		if (dup2(pipefds[R], STDIN_FILENO) == -1)
			die("dup2");
		close(pipefds[R]);

		if (execve(argv[4], cmd_args2, env) == -1)
			die("execve");
	}
	return (0);
}

