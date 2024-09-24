/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:19:02 by sishige           #+#    #+#             */
/*   Updated: 2024/09/24 20:09:30 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_pipex pipex, char **cmd_args, int pipefds[2], int i)
{
	close(pipefds[R]);
	if (i < pipex.n_cmds - 1)
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup2");
	close(pipefds[W]);
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

static int	wait_process(pid_t pid, int n_cmds)
{
	int	i;
	int	wait_stat;
	int	exit_stat;

	i = 0;
	while (i < n_cmds - 1)
	{
		wait(&wait_stat);
		i++;
	}
	exit_stat = 0;
	waitpid(pid, &wait_stat, 0);
	if (WIFEXITED(wait_stat))
		exit_stat = WEXITSTATUS(wait_stat);
	else if (WIFSIGNALED(wait_stat))
		exit_stat = WTERMSIG(wait_stat);
	return (exit_stat);
}

int	create_process(t_pipex pipex)
{
	int		pipefds[2];
	pid_t	pid;
	char	**cmd_args;
	int		i;

	i = 0;
	while (i < pipex.n_cmds)
	{
		cmd_args = ft_split(pipex.cmds[i], ' ');
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
	return (wait_process(pid, pipex.n_cmds));
}
