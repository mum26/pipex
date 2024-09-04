/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:48:41 by sishige           #+#    #+#             */
/*   Updated: 2024/08/24 23:08:05 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *name)
{
	char	**env;
	size_t	len;

	env = environ;
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	while (env)
	{
		if (ft_strlen(*env) < len)
		{
			env++;
			continue ;
		}
		if (!ft_strncmp(*env, name, len) && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

// int main(int argc, char *argv[])
//{
//	if (argc < 2)
//		return (0);
//	char **dir = ft_split(ft_getenv(argv[1]), ':');
//	while (*dir)
//	{
//		printf("%s\n", *dir++);
//	}
//}
