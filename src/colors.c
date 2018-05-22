/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 05:53:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 21:10:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static bool	is_color_char(char c)
{
	return (('A' <= c && c <= 'H') || ('a' <= c && c <= 'h') || c == 'x');
}

static char	*get_color_pair(char *p, char *lscolors)
{
	if (*lscolors != 'x')
	{
		if (!(*lscolors & 32))
		{
			*p++ = '1';
			*p++ = ';';
		}
		*p++ = '3';
		*p++ = TO_CHAR((*lscolors | 32) - 'a');
	}
	if (lscolors[1] && lscolors[1] != 'x')
	{
		*p++ = ';';
		*p++ = '4';
		*p++ = TO_CHAR((lscolors[1] | 32) - 'a');
	}
	return (p);
}

void		get_colors(t_ls *info)
{
	uint8_t		i;
	char		*lscolors;
	char		*p;

	if (info->colored_output && (lscolors = getenv("LSCOLORS")) != NULL)
	{
		i = 0;
		while (*lscolors && i < COLOR_INDEXES)
		{
			p = info->ctab[i++];
			if (!is_color_char(*lscolors))
			{
				info->colored_output = false;
				return ;
			}
			*p++ = '';
			*p++ = '[';
			p = get_color_pair(p, lscolors);
			lscolors += 2;
			*p++ = 'm';
			*p = 0;
			info->len_color[i - 1] = p - info->ctab[i - 1];
		}
	}
}

char		*ft_strcpy_color(char *bufp, const char *color, size_t color_len)
{
	ft_strcpy(bufp, color);
	return (bufp + color_len);
}
