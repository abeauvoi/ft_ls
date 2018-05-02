/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 05:33:13 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:21:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
	if (entry->sbuf.st_uid > info->max_uid)
		info->max_uid = entry->sbuf.st_uid;
	if (entry->sbuf.st_gid > info->max_gid)
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

//static void	print_dir_name(t_ls *info, const char *path, size_t pathlen)
//{
//	char	buf[PATH_MAX + 3];
//	size_t	len;
//
//	len = MIN(pathlen, PATH_MAX);
//	ft_strncpy(buf, path, len);
//	if (pathlen > PATH_MAX)
//	{
//		buf[PATH_MAX - 3] = '.';
//		buf[PATH_MAX - 2] = '.';
//		buf[PATH_MAX - 1] = '.';
//	}
//	buf[len++] = ':';
//	buf[len++] = '\n';
//	buf[len] = 0;
//	bufferize_str(info, buf, len);
//}

//static void		print_total_blocks(t_ls *info, blkcnt_t total_blocks)
//{
//	char	cbuf[INT_BUFSIZE_BOUND(blkcnt_t) + 1];
//	char	*endptr;
//	char	*startptr;
//
//	endptr = cbuf + sizeof(cbuf) - 1;
//	*endptr = 0;
//	startptr = ft_ultoa(endptr, total_blocks);
//	bufferize_str(info, startptr, endptr - startptr);
//}

void		read_current_dir(t_ls *info, t_fileinfo **entries,
		t_fileinfo **dirs, DIR *dirp)
{
	blkcnt_t		total_blocks;
	t_fileinfo		*tmp;
	struct dirent	*de;
	t_fileinfo		*fp;

	if (info->nb_args > 1)
	//	print_dir_name(info, (*dirs)->path, (*dirs)->pathlen);
		ft_printf("%s:\n", (*dirs)->path);
	total_blocks = 0;
	tmp = NULL;
	while ((de = readdir(dirp)) != NULL)
	{
		if (display_entry(de->d_name, info->options))
		{
			fp = init_node(*dirs, de);
			update_max_values(info, fp);
			lstinsert(entries, fp, *info);
			total_blocks += fp->sbuf.st_blocks;
		}
	}
	lstdel_head(dirs, &info->dirs);
	if (info->options & LONG_LIST && *entries)
		// print_total_blocks(&info, total_blocks);
		ft_printf("total %llu\n", total_blocks);
	display_entries(entries, &tmp, info);
	add_subdirs_to_dirs(dirs, &tmp);
	if (*dirs)
		// bufferize_char(info, '\n');
		ft_putchar('\n');
}
