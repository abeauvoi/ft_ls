/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:33:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 06:20:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "ft_ls.h"

void		lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls_opts options)
{
	t_fileinfo	*cur;

	if (*head == NULL)
		*head = entry;
	else
	{
		if (cmp(entry, *head, options))
		{
			entry->next = *head;
			*head = entry;
			return ;
		}
		cur = *head;
		while (cur->next && !(cmp(entry, cur->next, options)))
			cur = cur->next;
		entry->next = cur->next;
		cur->next = entry;
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

void	lstpop(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head)->next;
	if (!(*head)->is_cmd_line_arg)
		free((void*)(*head)->name);
	free((void*)(*head)->linkname);
	free((void*)(*head)->path);
	free(*head);
	(*head) = tmp;
}

t_fileinfo	*init_node(t_fileinfo *cur_dir, struct dirent *de)
{
	t_fileinfo		*fp;
	struct stat		sbuf;

	fp = lstnew();
	fp->name = ft_strdup(de->d_name);
	fp->namlen = de->d_namlen;
	if (!(fp->path = concat_path(cur_dir->name, fp->name, cur_dir->namlen,
					fp->namlen)))
		perror_and_exit();
	lstat(fp->path, &sbuf);
	fp->filetype = get_filetype(sbuf.st_mode);
	fp->stat_ok = 1;
	if (fp->filetype == SYMBOLIC_LINK)
		fp->linkok = 1;
	fp->errno_dup = errno;
	fp->sbuf = sbuf;
	return (fp);
}
