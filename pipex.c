/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/19 22:06:31 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *pipex, char **cmd_args, int pipefds[2], int i)
{
	close(pipefds[R]);
	if (i < pipex->n_cmds - 1)
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup2");
	close(pipefds[W]);
	ft_execvp(cmd_args[0], cmd_args);
	ft_fprintf(stderr, "bash: %s: command not found\n", cmd_args[0]);
	exit(1);
}

void	parent_process(int pipefds[2])
{
	close(pipefds[W]);
	if (dup2(pipefds[R], STDIN_FILENO) == -1)
		die("dup2");
	close(pipefds[R]);
}

void	create_process(t_pipex *pipex)
{
	int		pipefds[2];
	pid_t	pid;
	char	**cmd_args;
	int		i;

	i = 0;
	while (i < pipex->n_cmds)
	{
		cmd_args = ft_split(pipex->cmds[i], ' ');
		if (cmd_args == NULL)
			die("ft_split");
		if (pipe(pipefds) == -1)
			die("pipe");
		pid = fork();
		if (pid == -1)
			die("fork");
		if (pid == 0)
			child_process(pipex, cmd_args, pipefds, i);
		else
			parent_process(pipefds);
		cleanup(cmd_args);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_pipex	pipex;

	if (argc < 5)
		die("arguments 足りない");
	init_pipex(&pipex, argc, argv);
	set_input(pipex.in_file);
	set_output(pipex.out_file);
	create_process(&pipex);
	return (0);
}
