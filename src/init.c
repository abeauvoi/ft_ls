/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:59:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 07:00:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init(t_ls *info)
{
	ft_bzero(info, sizeof(*info));
	info->outf = short_format;
}

void	setup(t_ls *info)
{
	if (info->options & LONG_LIST)
		info->outf = long_format;
	if (info->options & SIZE_SORT)
		info->options &= ~MODIF_SORT;
}
