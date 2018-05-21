/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:59:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 06:23:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ls.h"

void		init(t_ls *info)
{
	ft_bzero(info, sizeof(*info));
	info->outf = short_format;
	info->cmpf = cmp;
	info->a = info->buf;
	info->z = info->buf + FT_LS_BUFSIZ;
	if (isatty(STDOUT_FILENO))
		info->colored_output = true;
	get_colors(info);
}

const char	**setup(t_ls *info, const char **argv)
{
	if (info->options & LONG_LIST)
		info->outf = long_format;
	if (info->options & SIZE_SORT)
		info->options &= ~MODIF_SORT;
	if (info->options & REVERSE)
		info->cmpf = rev_cmp;
	if (*argv == NULL)
		*(--argv) = ".";
	return (argv);
}
