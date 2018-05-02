/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:13:56 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/03 01:29:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	display_filetype_char(t_fileinfo *entry)
{
	if (entry->filetype == DIRECTORY)
		return ('/');
	else if (entry->filetype == NORMAL
			&& (entry->sbuf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return ('*');
	else if (entry->filetype == SYMBOLIC_LINK)
		return ('@');
	else if (entry->filetype == SOCK)
		return ('=');
	else if (entry->filetype == WHITEOUT)
		return ('%');
	else if (entry->filetype == FIFO)
		return ('|');
	return ('?');
}
