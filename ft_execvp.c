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
	char **temp = substrs;

	while (*temp)
	{
		free(*temp);
		*temp = NULL;
		temp++;
	}
	free(substrs);
	substrs = NULL;
}

int	ft_execvp(char *file, char *const argv[])
{
	char	**dirs;
	char	*full_path;
	char	*file_path;
	char	*temp_path;
	size_t	i;

	if (ft_strchr(file, '/'))
	{
		execve(file, argv, environ);
		die("exeve");
	}
	dirs = ft_split(ft_getenv("PATH"), ':');
	if (!dirs)
		return (-1);
	full_path = NULL;
	file_path = ft_strjoin("/", file);
	i = 0;
	while (dirs[i])
	{
		temp_path = ft_strjoin(dirs[i], file_path);
		if (!access(temp_path, X_OK))
		{
			full_path = temp_path;
			break ;
		}
		free(temp_path);
		i++;
	}
	free(file_path);
	if (full_path)
	{
		execve(full_path, argv, environ);
		free(full_path);
	}
	return (cleanup(dirs), -1);
}

//__attribute__((destructor)) static void destructor(void)
//{
//	system("leaks -q a.out");
//}
//
//int	main(int argc, char *argv[])
//{
//	(void)argc;
//	ft_execvp(argv[1], &argv[1]);
//	perror("ft_execvp");
//	exit(1);
//}
