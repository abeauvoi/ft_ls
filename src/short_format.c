/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 06:58:04 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 06:36:30 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	short_format(t_fileinfo *entry, t_ls *info)
{
	char	buf[255 + 1 + 1];

	ft_strcpy_non_printable_chars(buf, entry->name);
	buf[entry->namlen] = '\n';
	buf[entry->namlen + 1] = 0;
	strtobuf(info, buf, entry->namlen + 1);
}
