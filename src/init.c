/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:59:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 06:34:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init(t_ls *info)
{
	ft_bzero(info, sizeof(*info));
	info->outf = short_format;
}

void	setup(t_ls *info, const char *const *argv)
{
	if (info->options & LONG_LIST)
		info->outf = long_format;
	if (info->options & SIZE_SORT)
		info->options &= ~MODIF_SORT;
	info->has_no_arg = *argv == NULL;
}
