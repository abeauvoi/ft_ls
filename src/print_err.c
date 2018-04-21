/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:46:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/21 01:11:28 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"

void	print_error_and_exit(const char *format, const char *error,
		const char *arg)
{
	ft_printf(format, 2, error, *arg);
	print_usage();
	exit(EXIT_FAILURE);
}

void	perror_and_exit(void)
{
	perror("ft_ls: Error");
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
		ft_strcpy(buf, "ft_ls: ");
		ft_strcpy(buf + 7, arg);
		perror(buf);
	}
	errno = 0;
	free(if_too_long);
}
