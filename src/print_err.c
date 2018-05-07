/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:46:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 05:37:54 by abeauvoi         ###   ########.fr       */
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

void	ft_perror(const char *arg, size_t arglen, t_ls *info)
{
	char	buf[MAXNAMLEN + MAX_ERR_SIZE + sizeof("ft_ls: : ")];
	char	*bufp;
	char	*errmsg;

	bufp = buf;
	ft_strcpy(bufp, "ft_ls: ");
	bufp += 7;
	ft_strcpy(bufp, arg);
	bufp += arglen;
	ft_strcpy(bufp, ": ");
	bufp += 2;
	ft_strcpy(bufp, errmsg = strerror(errno));
	bufp += ft_strlen(errmsg);
	*bufp++ = '\n';
	*bufp = 0;
	errno = 0;
	strtobuf(info, buf, bufp - buf);
}
