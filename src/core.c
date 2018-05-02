/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:22:18 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool	display_entry(const char *arg, t_ls_opts options)
{
	return !(*arg == '.'
			&& (!(options & (ALL | ALMOST_ALL))
				|| ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))));
}

void	display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		t_ls *info)
{
	while (*entries)
	{
		info->outf(*entries, *info);
		if (tmp && (info->options & RECURSIVE)
				&& (*entries)->filetype == DIRECTORY)
		{
			++info->nb_args;
			lstpush(tmp, lstpop(entries));
		}
		else
			lstdel_head(entries, &info->entries);
	}
}

void	add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo **tmp)
{
	t_fileinfo	*ptr;

	if (!*tmp)
		return ;
	ptr = *tmp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = (*dirs);
	(*dirs) = (*tmp);
	(*tmp) = NULL;
}

static void	clear_info_current_dir(t_ls *info)
{
	info->max_block_size = 0;
	info->max_gid = 0;
	info->max_uid = 0;
	info->max_inode = 0;
	info->max_major = 0;
	info->max_minor = 0;
	info->max_nlink = 0;
	info->max_file_size = 0;
	info->max_block_size = 0;
	ft_bzero(info->long_format_col_widths,
			sizeof(info->long_format_col_widths));
}

void	core(t_ls info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR				*dirp;

	display_entries(&entries, NULL, &info);
	while (dirs)
	{
		if (!(dirp = opendir(dirs->path)))
		{
			ft_perror(dirs->name);
			lstdel_head(&dirs, &info.dirs);
		}
		else
		{
			read_current_dir(&info, &entries, &dirs, dirp);
			if (closedir(dirp) == -1)
				ft_perror(dirs->path);
			clear_info_current_dir(&info);
		}
	}
}
