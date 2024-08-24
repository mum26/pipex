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
	char	*path;
	char	*file_path;
	size_t	i;

	dirs = ft_split(ft_getenv("PATH"), ':');
	if (!dirs)
		return (-1);
	file_path = ft_strjoin("/", file);
	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin(dirs[i], file_path);
		if (!access(path, X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	execve(path, argv, environ);
	return (cleanup(dirs), free(file_path), free(path), -1);
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
