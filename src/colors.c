/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 05:53:36 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 06:21:10 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static bool	is_color_char(char c)
{
	return (('A' <= c && c <= 'H') || ('a' <= c && c <= 'h') || c == 'x');
}

void		get_colors(t_ls *info)
{
	uint8_t		i;
	char		*lscolors;
	char		*p;

	if (info->colored_output && (lscolors = getenv("LSCOLORS")) != NULL
			&& *lscolors)
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
			if (*lscolors != 'x')
			{
				if (!(*lscolors & 32))
				{
					*lscolors |= 32;
					*p++ = '1';
					*p++ = ';';
				}
				*p++ = '3';
				*p++ = TO_CHAR(*lscolors - 'a');
			}
			if (lscolors[1] && lscolors[1] != 'x')
			{
				*p++ = ';';
				lscolors[1] |= 32;
				*p++ = '4';
				*p++ = TO_CHAR(lscolors[1] - 'a');
			}
			lscolors += 2;
			*p++ = 'm';
			*p = 0;
			info->len_color[i - 1] = p - info->ctab[i - 1];
		}
	}
}

char		*ft_strcpy_color(char *bufp, const char *ansi_color,
		size_t ansi_color_len)
{
	ft_strcpy(bufp, ansi_color);
	return (bufp + ansi_color_len);
}
