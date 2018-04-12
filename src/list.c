/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:33:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 06:59:33 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"

static t_bool		cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	t_bool	t;

	t = (ft_strcmp(arg1->name, arg2->name) < 0) ^ (options & REVERSE);
	if (options & MODIF_SORT)
		t = ((arg1->sbuf.st_mtimespec.tv_sec / 60)
				< (arg2->sbuf.st_mtimespec.tv_sec / 60)) ^ (options & REVERSE);
	else if (options & SIZE_SORT)
		t = ((arg1->sbuf.st_size) > (arg2->sbuf.st_size)) ^ (options & REVERSE);
	return (t);
}

void		lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls_opts options)
{
	t_fileinfo	*tmp;

	if (*head == NULL)
		*head = entry;
	else
	{
		tmp = *head;
		while (tmp->next != NULL && !cmp(entry, tmp, options))
			tmp = tmp->next;
		if (tmp == *head)
			entry->next = *head;
		else
		{
			entry->next = tmp->next;
			tmp->next = entry;
		}
	}
}
		
t_fileinfo	*lstnew(const char *name, const char *path, size_t namlen,
		t_bool is_dup)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(*new))))
		perror_and_exit();
	ft_bzero(new, sizeof(*new));
	new->name = name;
	new->path = path;
	new->is_dup = is_dup;
	new->stat_ok = lstat(name, &new->sbuf);
	new->errno_dup = errno;
	errno = 0;
	new->filetype = new->sbuf.st_mode & S_IFMT;
	new->linkok = S_ISLNK(new->sbuf.st_mode);
	new->namlen = namlen;
	return (new);
}

t_fileinfo		*lstpop(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = *head;
	(*head) = (*head)->next;
	return (tmp);
}

void	del_entry(t_fileinfo *entry)
{
	if (entry->is_dup)
		free((void*)entry->name);
	free((void*)entry->linkname);
	free((void*)entry->path);
	free(entry);
}
