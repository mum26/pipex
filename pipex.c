/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/18 20:22:25 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_input(t_pipex *pipex)
{
	int	input_fd;
	int	stat;

	stat = 0;
	if (access(pipex->in_file, F_OK | R_OK) == 0)
	{
		input_fd = open(pipex->in_file, O_RDONLY);
		if (input_fd == -1)
			perror("open");
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(input_fd);
	}
	else
	{
		input_fd = open("/dev/null", O_RDONLY);
		if (input_fd == -1)
			perror("open");
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(input_fd);
		stat = warn(pipex->out_file);
	}
	return (stat);
}

void	set_output(t_pipex *pipex)
{
	int	output_fd;

	if (access(pipex->out_file, F_OK) == 0 
			&& access(pipex->out_file, W_OK) == -1)
		panic(pipex->out_file);
	else
	{
		if (pipex->mode)
			output_fd = open(pipex->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			output_fd = open(pipex->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1)
			die("open");
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			die("dup2");
		close(output_fd);
	}
}

void	init_pipex(t_pipex *pipe, int argc, char **argv)
{
	pipe->in_file = argv[1];
	pipe->out_file = argv[argc - 1];
	pipe->mode = 1;
	pipe->cmds = &argv[2];
	pipe->n_cmds = argc - 3;
	pipe->stat = 0;
	pipe->lim = argv[2];
}

void	child_process(char *file, char **cmd_args, int pipefds[2], int i)
{
	close(pipefds[R]);
	if (i < pipex->n_cmds - 1)
		if (dup2(pipefds[W], STDOUT_FILENO) == -1);
			die("dup2");
	close(pipefds[W]);
	ft_exevp(cmd, cmd_args);
	ft_fprintf(stderr, "bash: %s: cmmand not found\n" cmd);
	exit(1);
}

void	parent_process(int pipefds[2])
{
	close(pipefds[W]);
	if (dup2(pipefds[R], STDIN_FILENO) == -1)
		die("dup2");
	close(pipefds[R]);
}

int	create_process(t_pipex *pipex)
{
	int		pipefds[2];
	pid_t	pid;
	char	**cmd_args;
	int		i;

	if (pipe(pipefds) == -1)
		die("pipe");

	i = 0;
	while (i < n_cmds - 1)
	{
		cmd_args = ft_split(pipex->cmds[i]);
		if (cmd_args == NULL)
			die("ft_split");
		if (pipe(pipefds) == -1)
			die("pipe");
		pid = fork();
		if (pid == -1)
			die("fork");
		if (pid == 0)
			child_process(cmd_args[0], cmd_args, pipefds, i);
		else
			parent_process(pipefds);
		cleanup(cmd_args);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pipefds[2];
	pid_t	pid;
	t_pipex	pipex;

//	start
	if (argc < 5)
		die("arguments 足りない");
//	io file se
	init_pipex(&pipex, argc, argv);
	set_input(&pipex);
	set_output(&pipex);

// create pipe
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
		if (ft_execvp(cmd_args1[0], cmd_args1) == -1)
			die("ft_execvp");
	}
	else
	{
		wait(NULL);
		close(pipefds[W]);
		if (dup2(pipefds[R], STDIN_FILENO) == -1)
			die("dup2");
		close(pipefds[R]);
		if (ft_execvp(cmd_args2[0], cmd_args2) == -1)
			die("ft_execvp");
	}
	return (0);
}

