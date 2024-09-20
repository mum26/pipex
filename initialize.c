/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:33:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/20 17:39:54 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipe, int argc, char **argv)
{
	pipe->in_file = argv[1];
	pipe->out_file = argv[argc - 1];
	pipe->cmds = &argv[2];
	pipe->n_cmds = argc - 3;
	pipe->stat = 0;
}

int	set_input(char *file)
{
	int	input_fd;
	int	stat;

	stat = 0;
	if (access(file, F_OK | R_OK) == 0)
	{
		input_fd = open(file, O_RDONLY);
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
		stat = warn(file);
	}
	return (stat);
}

void	set_output(char *file)
{
	int	output_fd;
	if (access(file, F_OK) == 0 
			&& access(file, W_OK) == -1)
		panic(file);
	else
	{
		output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
			die("open");
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			die("dup2");
		close(output_fd);
	}
}
