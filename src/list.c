/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:33:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/01 05:36:28 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "ft_ls.h"

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

t_fileinfo	*lstpop(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}

t_fileinfo	*init_node(t_fileinfo *cur_dir, struct dirent *de)
{
	t_fileinfo		*fp;
	struct stat		sbuf;

	fp = lstnew();
	fp->name = ft_strdup(de->d_name);
	fp->namlen = de->d_namlen;
	if (!(fp->path = concat_path(cur_dir->path, fp->name, cur_dir->pathlen,
					fp->namlen)))
		perror_and_exit();
	fp->pathlen = cur_dir->pathlen + fp->namlen
		+ (cur_dir->path[cur_dir->pathlen - 1] == '/' ? 0 : 1);
	fp->stat_ok = lstat(fp->path, &sbuf) == 0;
	fp->filetype = get_filetype(sbuf.st_mode);
	fp->sbuf = sbuf;
	return (fp);
}
