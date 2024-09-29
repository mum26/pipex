/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:08 by sishige           #+#    #+#             */
/*   Updated: 2024/09/21 21:38:19 by sishige          ###   ########.fr       */
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
# include <errno.h>

typedef struct s_pipex
{
	char		*infile;
	char		*outfile;
	char *const	*cmds;
	int			n_cmds;
	char *const	*envp;
}				t_pipex;

int			create_process(t_pipex pipex);

void		die(const char *cause);
void		panic(const char *cause);
int			warn(const char *cause);

char		*ft_getenv(char *name, char *const envp[]);
int			ft_execvpe(char *file, char *const argv[], char *const envp[]);

#endif
