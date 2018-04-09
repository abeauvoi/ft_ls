/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:59:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 09:50:00 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init(t_ls *info)
{
	info->options = 0;
	info->outf = short_format;
}

void	setup(t_ls *info)
{
	if (info->options & LONG_LIST)
		info->outf = long_format;
}
