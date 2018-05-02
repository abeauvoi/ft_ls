/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:46:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:15:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_printf.h"
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

void	ft_perror(const char *arg)
{
	char	buf[MAXNAMLEN + MAX_ERR_SIZE + sizeof("ft_ls: : ")];

	strcpy(buf, "ft_ls: ");
	strcpy(buf + 7, arg);
	strcat(buf, ": ");
	strcat(buf, strerror(errno));
	errno = 0;
	ft_putendl_fd(buf, 2);
}
