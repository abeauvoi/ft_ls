/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:46:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/11 04:28:13 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"

void	print_error_and_exit(const char *error,
		const char *arg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(" -- (", 2);
	ft_putchar_fd(*arg, 2);
	ft_putstr_fd(")\n", 2);
	print_usage();
	exit(EXIT_FAILURE);
}

inline void	ft_perror(const char *arg)
{
	char	buf[256];
	char	*if_too_long;

	if_too_long = NULL;
	if (ft_strlen(arg) > 248)
	{
		if_too_long = ft_strjoin("ft_ls: ", arg);
		perror(if_too_long);
	}
	else
	{
		ft_bzero(buf, 256);
		ft_strcpy(buf, "ft_ls: ");
		ft_strcpy(buf + 7, arg);
		perror(buf);
	}
	errno = 0;
	free(if_too_long);
}
