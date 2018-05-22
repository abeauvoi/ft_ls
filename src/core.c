/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 00:21:42 by abeauvoi         ###   ########.fr       */
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

void		display_entries(t_fileinfo **entries, t_fileinfo **subdirs,
		t_ls *info)
{
	t_fileinfo	*first_entry;

	while (*entries)
	{
		first_entry = lstpop(entries);
		info->outf(first_entry, info);
		if (subdirs && (info->options & RECURSIVE)
				&& (first_entry->stat_ok ? S_ISDIR(first_entry->sbuf.st_mode) :
					first_entry->filetype == DIRECTORY)
				&& ft_strcmp(first_entry->name, ".") != 0
				&& ft_strcmp(first_entry->name, "..") != 0)
		{
			++info->nb_args;
			lstpush(subdirs, first_entry);
		}
		else
			lstdel_one(first_entry);
	}
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
	info->found_major_minor_dev = false;
	ft_bzero(info->lfmt_cwidth, sizeof(info->lfmt_cwidth));
}

void		print_dir_name(t_ls *info, const char *path, size_t pathlen)
{
	size_t	len;
	char	dir_name[PATH_MAX + 2 + 1];

	len = MIN(pathlen, PATH_MAX);
	ft_memcpy(dir_name, path, len);
	ft_strcpy(dir_name + len, ":\n");
	strtobuf(info, dir_name, len + 2);
}

int			core(t_ls *info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR			*dirp;

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
