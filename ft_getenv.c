/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:48:41 by sishige           #+#    #+#             */
/*   Updated: 2024/09/21 20:45:45 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *name, char *const envp[])
{
	char	**env;
	size_t	len;

	if (!name || !envp[])
		return (NULL);
	env = envp;
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
