/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/07 19:51:16 by sishige          ###   ########.fr       */
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
	pipe->mode = 0;
	pipe->cmds = &argv[2];
	pipe->n_cmds = argc - 3;
	pipe->stat = 0;
	pipe->lim = argv[2];
}

int	main(int argc, char **argv)
{
	int	iofds[2];
	int	pipefds[2];
	pid_t	pid;
	t_pipex	pipex;

	iofds[R] = open(argv[1], O_RDONLY);
	iofds[W] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char **cmd_args1 = ft_split(argv[2], ' ');
	char **cmd_args2 = ft_split(argv[3], ' ');

//	start
	if (argc < 5)
		die("arguments 足りない");
	

	init_pipex(&pipex, argc, argv);

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
			die("dup21");
		close(iofds[R]);
		if (dup2(pipefds[W], STDOUT_FILENO) == -1)
			die("dup22");
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

