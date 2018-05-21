/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:33:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 03:03:59 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "ft_printf.h"

void		lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls info)
{
	t_fileinfo	*cur;

	if (*head == NULL)
		*head = entry;
	else
	{
		if (info.cmpf(entry, *head, info.options))
		{
			entry->next = *head;
			*head = entry;
			return ;
		}
		cur = *head;
		while (cur->next && !(info.cmpf(entry, cur->next, info.options)))
			cur = cur->next;
		entry->next = cur->next;
		cur->next = entry;
	}
}

void		lstpush(t_fileinfo **head, t_fileinfo *entry)
{
	t_fileinfo	*tmp;
	
	if (*head == NULL)
		*head = entry;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = entry;
	}
}
		
t_fileinfo	*lstnew(void)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(*new))))
		perror_and_exit();
	ft_bzero(new, sizeof(*new));
	return (new);
}

static void	init_long_list_info(t_fileinfo *fp, bool stat_ok)
{
	struct passwd	*pwd;
	struct group	*grp;

	if (stat_ok && (pwd = getpwuid(fp->sbuf.st_uid)) != NULL)
	{
		fp->user_name = ft_strdup(pwd->pw_name);
		fp->user_name_length = ft_strlen(fp->user_name);
	}
	if (stat_ok && (grp = getgrgid(fp->sbuf.st_gid)) != NULL)
	{
		fp->group_name = ft_strdup(grp->gr_name);
		fp->group_name_length = ft_strlen(fp->group_name);
	}
}

t_fileinfo	*init_node(t_fileinfo *cur_dir, struct dirent *de, t_ls info)
{
	t_fileinfo		*fp;

	fp = lstnew();
	fp->name = ft_strdup(de->d_name);
	fp->namlen = de->d_namlen;
	if (!(fp->path = concat_path(cur_dir->path, fp->name, cur_dir->pathlen,
					fp->namlen)))
		perror_and_exit();
	fp->pathlen = cur_dir->pathlen + fp->namlen
		+ (cur_dir->path[cur_dir->pathlen - 1] == '/' ? 0 : 1);
	fp->stat_ok = lstat(fp->path, &fp->sbuf) == 0;
	if (info.options & LONG_LIST)
		init_long_list_info(fp, fp->stat_ok);
	fp->filetype = (de->d_type > 2 ? (de->d_type >> 1) + 1 : de->d_type);
	return (fp);
}
