/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:46:37 by sishige           #+#    #+#             */
/*   Updated: 2024/10/01 19:34:13 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_dirs(char *file, char *const envp[])
{
	char	*path;

	path = ft_getenv("PATH", envp);
	if (path == NULL)
	{
		ft_fprintf(stderr, "pipex: %s: %s\n", file, strerror(2));
		exit(127);
	}
	return (ft_split(path, ':'));
}

static char	*get_executable_path(char *file_path, char *const envp[])
{
	char	**dirs;
	char	*full_path;
	char	*temp_path;
	size_t	i;

	if (!file_path)
		return (NULL);
	dirs = get_dirs(file_path + 1, envp);
	if (!dirs)
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

	if (!file)
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
	if (full_path && *file)
	{
		execve(full_path, argv, envp);
		die("execve");
	}
	return (free(file_path), free(full_path), -1);
}
