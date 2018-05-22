/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 05:33:13 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 00:16:22 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			update_max_values(t_ls *info, t_fileinfo *entry)
{
	if (info->options & PRINT_INODE && entry->sbuf.st_ino > info->max_inode)
		info->max_inode = entry->sbuf.st_ino;
	if (info->options & PRINT_BLOCKS
			&& entry->sbuf.st_blocks > info->max_block_size)
		info->max_block_size = entry->sbuf.st_blocks;
	if (entry->sbuf.st_nlink > info->max_nlink)
		info->max_nlink = entry->sbuf.st_nlink;
	if (entry->user_name_length > info->lfmt_cwidth[OWNER_COL])
		info->lfmt_cwidth[OWNER_COL] = entry->user_name_length;
	else if (entry->sbuf.st_uid > info->max_uid)
		info->max_uid = entry->sbuf.st_uid;
	if (entry->group_name_length > info->lfmt_cwidth[GROUP_COL])
		info->lfmt_cwidth[GROUP_COL] = entry->group_name_length;
	else if (entry->sbuf.st_gid > info->max_gid)
		info->max_gid = entry->sbuf.st_gid;
	if (S_ISBLK(entry->sbuf.st_mode) || S_ISCHR(entry->sbuf.st_mode))
	{
		if (MAJOR(entry->sbuf.st_rdev) > info->max_major)
			info->max_major = MAJOR(entry->sbuf.st_rdev);
		if (MINOR(entry->sbuf.st_rdev) > info->max_minor)
			info->max_minor = MINOR(entry->sbuf.st_rdev);
	}
	else if (entry->sbuf.st_size > info->max_file_size)
		info->max_file_size = entry->sbuf.st_size;
}

void				add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo *subdirs)
{
	t_fileinfo	*ptr;

	ptr = subdirs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = (*dirs);
	(*dirs) = subdirs;
}

static void			print_total_blocks(t_ls *info, blkcnt_t total_blocks)
{
	char	buf[5 + 1 + INT_BUFSIZE_BOUND(blkcnt_t) + 1 + 1];
	char	*endptr;
	char	*startptr;
	size_t	len;

	ft_bzero(buf, INT_BUFSIZE_BOUND(blkcnt_t) + 8);
	ft_strcpy(buf, "total ");
	endptr = buf + sizeof(buf) - 1;
	*endptr-- = 0;
	*endptr = '\n';
	startptr = ft_ultoa(endptr, total_blocks, total_blocks < 0);
	++endptr;
	len = endptr - startptr;
	ft_memmove(buf + 6, startptr, len);
	strtobuf(info, buf, len + 6);
}

static blkcnt_t		loop(t_ls *info, DIR *dirp, t_fileinfo **entries,
		t_fileinfo *dirs)
{
	struct dirent	*de;
	t_fileinfo		*fp;
	blkcnt_t		total_blocks;

	total_blocks = 0;
	while ((de = readdir(dirp)) != NULL)
	{
		if (display_entry(de->d_name, info->options))
		{
			fp = init_node(dirs, de, *info);
			if (!info->found_major_minor_dev &&
					(fp->stat_ok ?
					S_ISBLK(fp->sbuf.st_mode) || S_ISCHR(fp->sbuf.st_mode) :
					fp->filetype == CHARDEV || fp->filetype == BLOCKDEV))
				info->found_major_minor_dev = true;
			if (fp->stat_ok && info->options & LONG_LIST)
			{
				update_max_values(info, fp);
				total_blocks += fp->sbuf.st_blocks;
			}
			lstinsert(entries, fp, *info);
		}
	}
	return (total_blocks);
}

void				read_current_dir(t_ls *info, t_fileinfo **entries,
		t_fileinfo **dirs, DIR *dirp)
{
	t_fileinfo		*subdirs;
	blkcnt_t		total_blocks;

	subdirs = NULL;
	total_blocks = loop(info, dirp, entries, *dirs);
	lstdel_head(dirs);
	if (info->options & LONG_LIST && *entries)
		print_total_blocks(info, total_blocks);
	display_entries(entries, &subdirs, info);
	if (subdirs)
		add_subdirs_to_dirs(dirs, subdirs);
	if (*dirs)
		chartobuf(info, '\n');
}
