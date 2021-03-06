/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:58:04 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/06/13 22:21:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	short_format(t_fileinfo *entry, t_ls *info)
{
	char	buf[255 + 1 + 1];

	ft_strncpy(buf, entry->name, MIN(255, entry->namlen));
	buf[entry->namlen] = '\n';
	buf[entry->namlen + 1] = 0;
	if (entry->ctab_index != NO_COLOR)
		strtobuf(info, info->ctab[entry->ctab_index],
				info->len_color[entry->ctab_index]);
	strtobuf(info, buf, entry->namlen + 1);
	if (entry->ctab_index != NO_COLOR)
		strtobuf(info, RESET_COLOR, 3);
}
