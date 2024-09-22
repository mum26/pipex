/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:08:16 by sishige           #+#    #+#             */
/*   Updated: 2024/09/21 22:00:22 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	set_input(char *file)
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

static void	set_output(char *file)
{
	int	output_fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
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

static void	init_pipex(t_pipex *pipex,
		int argc, char *const argv[], char *const envp[])
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmds = &argv[2];
	pipex->n_cmds = argc - 3;
	pipex->envp = envp;
}

int	main(int argc, char *const argv[], char *const envp[])
{
	int		stat;
	t_pipex	pipex;

	if (argc != 5)
		die("The number of arguments is different");
	init_pipex(&pipex, argc, argv, envp);
	stat = set_input(pipex.infile);
	set_output(pipex.outfile);
	stat = create_process(pipex);
	return (stat);
}
