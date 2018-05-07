/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 05:53:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 06:38:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

void		get_colors(t_ls *info)
{
	const char	*p;

	if (isatty(STDOUT_FILENO))
		info->use_env_colors = true;
	if (info->use_env_colors && (p = getenv("LSCOLORS")) != NULL && *p)
	{
		//add code to build color_table indexed by filetype;
		//result should give strtobuf(info, info->color_table[entry->filetype], ...);
	}
}
