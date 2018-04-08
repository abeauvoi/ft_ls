/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:46:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/08 23:11:56 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	print_error_and_exit(const char *format, const char *error,
		const char *arg)
{
	ft_printf(format, 2, error, *arg);
	exit(EXIT_FAILURE);
}
