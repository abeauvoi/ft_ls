/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 21:25:52 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool		display_entry(const char *arg, t_ls_opts options)
{
	return (!(*arg == '.'
			&& (!(options & (ALL | ALMOST_ALL))
				|| ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0))))));
}

void		display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		t_ls *info)
{
	while (*entries)
	{
		info->outf(*entries, info);
		if (tmp && (info->options & RECURSIVE)
				&& (*entries)->filetype == DIRECTORY
				&& ft_strcmp((*entries)->name, ".") != 0
				&& ft_strcmp((*entries)->name, "..") != 0)
		{
			++info->nb_args;
			lstpush(tmp, lstpop(entries));
		}
		else
			lstdel_head(entries);
	}
}

void		add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo *tmp)
{
	t_fileinfo	*ptr;

	if (!tmp)
		return ;
	ptr = tmp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = (*dirs);
	(*dirs) = tmp;
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
	info->found_major_minor_dev = 0;
	ft_bzero(info->lfmt_cwidth, sizeof(info->lfmt_cwidth));
}

int			core(t_ls *info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR		*dirp;

	display_entries(&entries, NULL, info);
	while (dirs)
	{
		if (info->nb_args > 1)
			print_dir_name(info, dirs->path, dirs->pathlen);
		if (!(dirp = opendir(dirs->path)))
		{
			ft_perror(dirs->name, dirs->namlen, info);
			lstdel_head(&dirs);
			if (dirs)
				chartobuf(info, '\n');
		}
		else
		{
			read_current_dir(info, &entries, &dirs, dirp);
			if (closedir(dirp) == -1)
				ft_perror(dirs->path, dirs->pathlen, info);
			clear_info_current_dir(info);
		}
	}
	if (info->buf != info->a)
		ft_ls_flush_buffer(info);
	return (0);
}
