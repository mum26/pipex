/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:46:37 by sishige           #+#    #+#             */
/*   Updated: 2024/09/21 23:06:54 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_executable_path(char *file_path, char *const envp[])
{
	char	**dirs;
	char	*full_path;
	char	*temp_path;
	size_t	i;

	dirs = ft_split(ft_getenv("PATH", envp), ':');
	if (!dirs || !file_path)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (dirs[i])
	{
		temp_path = ft_strjoin(dirs[i], file_path);
		if (access(temp_path, X_OK) == 0)
		{
			full_path = temp_path;
			break ;
		}
		free(temp_path);
		i++;
	}
	return (cleanup(dirs), full_path);
}

int	ft_execvpe(char *file, char *const argv[], char *const envp[])
{
	char	*full_path;
	char	*file_path;

	if (!file && !argv && !envp)
		return (-1);
	if (ft_strchr(file, '/'))
	{
		execve(file, argv, envp);
		die("exeve");
	}
	file_path = ft_strjoin("/", file);
	if (!file_path)
		die("ft_strjoin");
	full_path = get_executable_path(file_path, envp);
	free(file_path);
	if (full_path)
	{
		execve(full_path, argv, envp);
		free(full_path);
		die("execve");
	}
	return (-1);
}
