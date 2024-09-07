/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/08/25 00:13:44 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	iofds[2];
	int	pipefds[2];
	pid_t	pid;

	iofds[R] = open(argv[1], O_RDONLY);
	iofds[W] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char **cmd_args1 = ft_split(argv[2], ' ');
	char **cmd_args2 = ft_split(argv[3], ' ');

	if (pipe(pipefds) == -1)
		die("pipe");
	pid = fork();
	if (pid == -1)
		die("fork");

	if (pid == 0)
	{
		close(pipefds[R]);
		close(iofds[W]);
		if (dup2(iofds[R], STDIN_FILENO) == -1)
			die("dup2");
		close(iofds[R]);
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup2");
		close(pipefds[W]);

		if (ft_execvp(cmd_args1[0], cmd_args1) == -1)
			die("ft_execvp");
	}
	else
	{
		wait(NULL);
		close(pipefds[W]);
		close(iofds[R]);
		if (dup2(iofds[W], STDOUT_FILENO) == -1)
			die("dup2");
		close(iofds[W]);
		if (dup2(pipefds[R], STDIN_FILENO) == -1)
			die("dup2");
		close(pipefds[R]);

		if (ft_execvp(cmd_args2[0], cmd_args2) == -1)
			die("ft_execvp");
	}
	return (0);
}

