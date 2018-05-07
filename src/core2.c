/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 05:33:13 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 05:40:41 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		update_max_values(t_ls *info, t_fileinfo *entry)
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
	if (entry->filetype == CHARDEV || entry->filetype == BLOCKDEV)
	{
		if (MAJOR(entry->sbuf.st_rdev) > info->max_major)
			info->max_major = MAJOR(entry->sbuf.st_rdev);
		if (MINOR(entry->sbuf.st_rdev) > info->max_minor)
			info->max_minor = MINOR(entry->sbuf.st_rdev);
	}
	else if (entry->sbuf.st_size > info->max_file_size)
		info->max_file_size = entry->sbuf.st_size;
}

void			print_dir_name(t_ls *info, const char *path, size_t pathlen)
{
	char	dir_name[PATH_MAX + 2 + 1];

	ft_memcpy(dir_name, path, MIN(pathlen, PATH_MAX));
	ft_memcpy(dir_name + pathlen, ":\n", 2);
	pathlen += 2;
	dir_name[pathlen] = 0;
	strtobuf(info, dir_name, pathlen);
}

static void		print_total_blocks(t_ls *info, blkcnt_t total_blocks)
{
	char	cbuf[5 + 1 + INT_BUFSIZE_BOUND(blkcnt_t) + 1 + 1];
	char	*endptr;
	char	*startptr;
	size_t	len;

	len = 6;
	ft_memcpy(cbuf, "total ", len);
	endptr = cbuf + sizeof(cbuf) - 1;
	*endptr-- = 0;
	*endptr = '\n';
	startptr = ft_ultoa(endptr, total_blocks, total_blocks < 0);
	++endptr;
	len += endptr - startptr;
	ft_memmove(cbuf + 6, startptr, endptr - startptr);
	strtobuf(info, cbuf, len);
}

void		read_current_dir(t_ls *info, t_fileinfo **entries,
		t_fileinfo **dirs, DIR *dirp)
{
	blkcnt_t		total_blocks;
	t_fileinfo		*tmp;
	struct dirent	*de;
	t_fileinfo		*fp;

	total_blocks = 0;
	tmp = NULL;
	while ((de = readdir(dirp)) != NULL)
	{
		if (display_entry(de->d_name, info->options))
		{
			fp = init_node(*dirs, de, *info);
			if (fp->stat_ok && info->options & LONG_LIST)
			{
				total_blocks += fp->sbuf.st_blocks;
				update_max_values(info, fp);
			}
			if (fp->stat_ok)
				lstinsert(entries, fp, *info);
		}
	}
	lstdel_head(dirs, &info->dirs);
	if (info->options & LONG_LIST && *entries)
		print_total_blocks(info, total_blocks);
	display_entries(entries, &tmp, info);
	add_subdirs_to_dirs(dirs, &tmp);
	if (*dirs)
		chartobuf(info, '\n');
}
