/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 04:39:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 06:29:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_color_executable(mode_t mode)
{
	if (mode & S_ISUID)
		return (COLOR_EXEC_SETUID);
	else if (mode & S_ISGID)
		return (COLOR_EXEC_SETGID);
	else
		return (COLOR_EXEC);
}

int			get_color_table_index(mode_t mode)
{
	if (S_ISREG(mode) && (mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return (get_color_executable(mode));
	else if (S_ISDIR(mode))
	{
		if (mode & S_IWOTH)
			return (mode & S_ISTXT ? COLOR_DIR_OTH_S : COLOR_DIR_OTH_NO_S);
		else
			return (COLOR_DIR);
	}
	else if (S_ISLNK(mode))
		return (COLOR_LINK);
	else if (S_ISSOCK(mode))
		return (COLOR_SOCK);
	else if (S_ISFIFO(mode))
		return (COLOR_FIFO);
	else if (S_ISBLK(mode))
		return (COLOR_BDEV);
	else if (S_ISCHR(mode))
		return (COLOR_CDEV);
	return (NO_COLOR);
}
