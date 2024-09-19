/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:26:00 by sishige           #+#    #+#             */
/*   Updated: 2024/09/19 21:03:42 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	die(const char *cause)
{
	perror(cause);
	exit(1);
}

void	panic(char *cause)
{
	int		err_num;
	char	*err_msg;

	err_num = errno;
	err_msg = strerror(err_num);
	ft_fprintf(stderr, "bash: %s: %s\n", cause, err_msg);
	exit(1);
}

int	warn(char *cause)
{
	int		err_num;
	char	*err_msg;

	err_num = errno;
	err_msg = strerror(err_num);
	ft_fprintf(stderr, "bash: %s: %s\n", cause, err_msg);
	return (err_num);
}
