/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:08 by sishige           #+#    #+#             */
/*   Updated: 2024/09/19 22:12:21 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define R 0
# define W 1

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

extern char	**environ;
extern int	errno;

typedef struct s_pipex
{
	char	*in_file;
	char	*out_file;
	char	**cmds;
	int		n_cmds;
	int		stat;
}			t_pipex;

void		die(const char *cause);
void		panic(char *cause);
int			warn(char *cause);

int			set_input(char *file);
void		set_output(char *file);
void		init_pipex(t_pipex *pipex, int argc, char **argv);

char		*ft_getenv(char *name);
int			ft_execvp(char *file, char *const argv[]);

#endif
