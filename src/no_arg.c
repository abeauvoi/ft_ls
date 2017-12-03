/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:23:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/19 16:23:53 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_ls.h"

void			no_arg(const char *const path)
{
	DIR				*dirp;
	struct dirent	*entry;

	if (!(dirp = opendir(path)))
		print_err(FTLS_ERR_FMT_B, path, strerror(errno), 1);
	while ((entry = readdir(dirp)) != NULL)
	{
		if (errno != 0)
			print_err(FTLS_ERR_FMT_B, "readdir", strerror(errno), 0);
		ft_putendl(entry->d_name);
	}
	if (closedir(dirp) == -1)
		print_err(FTLS_ERR_FMT_B, "closedir", strerror(errno), 0);
}
