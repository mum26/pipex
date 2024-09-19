/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:08 by sishige           #+#    #+#             */
/*   Updated: 2024/09/18 20:22:26 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define R 0
# define W 1

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

extern char	**environ;
extern int	errno;

typedef struct s_pipex
{
	char	*in_file;
	char	*out_file;
	int		mode;
	char	**cmds;
	int		n_cmds;
	int		stat;
	char	*lim;
}				t_pipex;

void	die(const char *cause);
void	panic(char	*cause);
int		warn(char	*cause);

int		set_input(t_pipex *pipex);
void	set_output(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int argc, char **argv);

char	*ft_getenv(char *name);
int		ft_execvp(char *file, char *const argv[]);
void	cleanup(char **substrs);

#endif
