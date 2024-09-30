/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:19:02 by sishige           #+#    #+#             */
/*   Updated: 2024/09/30 18:52:32 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_pipex pipex, char **cmd_args, int i)
{
	if (i == 0)
	{
		close(pipex.pipes[i].fds[R]);
		if (set_input(pipex.infile))
			exit(EXIT_FAILURE);
	}
	if (i == pipex.n_cmds - 1)
		set_output(pipex.outfile);
	else
	{
		if (dup2(pipex.pipes[i].fds[W], STDOUT_FILENO) == -1)
			die("dup2");
	}
	close(pipex.pipes[i].fds[W]);
	ft_execvpe(cmd_args[0], cmd_args, pipex.envp);
	ft_fprintf(stderr, "pipex: %s: command not found\n", cmd_args[0]);
	exit(127);
}

static void	parent_process(int pipefds[2])
{
	close(pipefds[W]);
	if (dup2(pipefds[R], STDIN_FILENO) == -1)
		die("dup2");
	close(pipefds[R]);
}

static int	wait_process(pid_t *pids, int n_cmds)
{
	int	i;
	int	wait_stat;
	int	exit_stat;

	i = 0;
	while (i < n_cmds)
	{
		waitpid(pids[i], &wait_stat, 0);
		i++;
	}
	exit_stat = 0;
	if (WIFEXITED(wait_stat))
		exit_stat = WEXITSTATUS(wait_stat);
	else if (WIFSIGNALED(wait_stat))
		exit_stat = WTERMSIG(wait_stat);
	return (exit_stat);
}

int	create_process(t_pipex pipex)
{
	pid_t	*pids;
	char	**cmd_args;
	int		i;

	pids = (pid_t *)malloc(sizeof(pid_t) * pipex.n_cmds);
	if (pids == NULL)
		die("malloc");
	i = 0;
	while (i < pipex.n_cmds)
	{
		cmd_args = ft_split(pipex.cmds[i], ' ');
		if (cmd_args == NULL)
			die("ft_split");
		pids[i] = fork();
		if (pids[i] == -1)
			die("fork");
		if (pids[i] == 0)
			child_process(pipex, cmd_args, i);
		else if (i != pipex.n_cmds - 1)
			parent_process(pipex.pipes[i].fds);
		cleanup(cmd_args);
		i++;
	}
	return (wait_process(pids, pipex.n_cmds));
}
