/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 05:53:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/18 09:39:57 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static void	get_color_pair(const char *lscolors, char color_buf[9 + 1])
{
	char	*p;

	p = color_buf;
	*p++ = '';
	if (!(*lscolors & 32))
	{
		*p++ = '1';
		*p++ = ';';
	}
	*p++ = 
}

static bool	is_color_char(char c)
{
	return (('A' <= c && c <= 'H') || ('a' <= c && c <= 'h') || c == 'x');
}

void		get_colors(t_ls *info)
{
	int			i;
	const char	*lscolors;
	const char	*tmp;
	char		*p;

	if (info->colored_output && (lscolors = getenv("LSCOLORS")) != NULL
			&& *lscolors)
	{
		i = 0;
		while (*tmp)
		{
			if (!is_color_char(*tmp))
				// err_mgmt;
			*p++ = '';
			if (*tmp != 'x')
			{
				if (!(*tmp & 32))
				{
					*p++ = '1';
					*p++ = ';';
				}
				*p++ = '3';
				*p++ = *tmp - ('A' | (*tmp & 32));
				++tmp;
			}
			if (*tmp != 'x')
			{
			++i;
		}
	}
}
