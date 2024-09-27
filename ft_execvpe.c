/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:46:37 by sishige           #+#    #+#             */
/*   Updated: 2024/09/27 22:34:31 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_dirs(char *file_path, char *const envp[])
{
	char	*path;

	path = ft_getenv("PATH", envp);
	if (path == NULL)
	{
		ft_fprintf(stderr, "pipex: %s: No such file or directory\n",
			file_path + 1);
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

	dirs = get_dirs(file_path, envp);
	if (dirs == NULL)
		die("ft_split");
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

void	execvpe_err_handling(char *file, char *path)
{
	if (path != NULL)
		err_msg = ft_strdup("command not found");
	else
		err_msg = ft_strdup("No such file or directory");
	if (file == NULL)
		file = ft_strdup("");
	ft_fprintf(stderr, "pipex: %s: %s\n", file, err_msg);
	exit(127);
}

int	ft_execvpe(char *file, char *const argv[], char *const envp[])
{
	char	*full_path;
	char	*file_path;
	char	*path;
	char	*err_msg;

	path = ft_getenv("PATH", envp);
	if (file == NULL || path == NULL)
		execvpe_err_handling(file, path);
	if (ft_strchr(file, '/'))
	{
		execve(file, argv, envp);
		panic(file);
	}
	file_path = ft_strjoin("/", file);
	if (!file_path)
		die("ft_strjoin");
	full_path = get_executable_path(file_path, envp);
	if (full_path)
	{
		execve(full_path, argv, envp);
		free(full_path);
		die("execve");
	}
	return (free(file_path), -1);
}
