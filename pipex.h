/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:08 by sishige           #+#    #+#             */
/*   Updated: 2024/09/20 19:47:12 by sishige          ###   ########.fr       */
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

int			create_process(char **cmds, int n_cmds);

void		die(const char *cause);
void		panic(const char *cause);
int			warn(const char *cause);

char		*ft_getenv(char *name);
int			ft_execvp(char *file, char *const argv[]);

#endif
