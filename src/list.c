/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:33:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/14 01:56:38 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	if ((*head)->is_cmd_line_arg)
		free((void*)(*head)->name);
	free((void*)(*head)->linkname);
	free((void*)(*head)->path);
	free(*head);
	(*head) = tmp;
}
