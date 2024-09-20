/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:33:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/20 20:12:48 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int n_cmds, char **cmd_args, int pipefds[2], int i)
{
	close(pipefds[R]);
	if (i < n_cmds - 1)
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup2");
	close(pipefds[W]);
	ft_execvp(cmd_args[0], cmd_args);
	ft_fprintf(stderr, "bash: %s: command not found\n", cmd_args[0]);
	exit(127);
}

static void	parent_process(int pipefds[2])
{
	close(pipefds[W]);
	if (dup2(pipefds[R], STDIN_FILENO) == -1)
		die("dup2");
	close(pipefds[R]);
}

static int	wait_process(pid_t pid, int n_cmds)
{
	int	i;
	int	stat;

	i = 0;
	while (i < n_cmds - 2)
	{
		wait(&stat);
		i++;
	}
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		stat = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
		stat = WTERMSIG(stat);
	return (stat);
}

int	create_process(char **cmds, int n_cmds)
{
	int		pipefds[2];
	pid_t	pid;
	char	**cmd_args;
	int		i;

	i = 0;
	while (i < n_cmds)
	{
		cmd_args = ft_split(cmds[i], ' ');
		if (cmd_args == NULL)
			die("ft_split");
		if (pipe(pipefds) == -1)
			die("pipe");
		pid = fork();
		if (pid == -1)
			die("fork");
		if (pid == 0)
			child_process(n_cmds, cmd_args, pipefds, i);
		else
			parent_process(pipefds);
		cleanup(cmd_args);
		i++;
	}
	return (wait_process(pid, n_cmds));
}
