/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:48:36 by sishige           #+#    #+#             */
/*   Updated: 2024/08/24 23:07:17 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup(char **substrs)
{
	char	**temp;

	temp = substrs;
	while (*temp)
	{
		free(*temp);
		*temp = NULL;
		temp++;
	}
	free(substrs);
	substrs = NULL;
}

static char	*get_executable_path(char *file_path)
{
	char	**dirs;
	char	*full_path;
	char	*temp_path;
	size_t	i;

	dirs = ft_split(ft_getenv("PATH"), ':');
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

int	ft_execvp(char *file, char *const argv[])
{
	char	*full_path;
	char	*file_path;

	if (ft_strchr(file, '/'))
	{
		execve(file, argv, environ);
		die("exeve");
	}
	file_path = ft_strjoin("/", file);
	if (!file_path)
		die("ft_strjoin");
	full_path = get_executable_path(file_path);
	free(file_path);
	if (full_path)
	{
		execve(full_path, argv, environ);
		free(full_path);
		die("execve");
	}
	return (-1);
}

__attribute__((destructor)) static void destructor(void)
{
	system("leaks -q a.out");
}

int	main(int argc, char *argv[])
{
	(void)argc;
//	ft_execvp(argv[1], &argv[1]);
//	perror("ft_execvp");
//	exit(1);
	ft_putstr_fd(get_executable_path(argv[1]), 1);
}
