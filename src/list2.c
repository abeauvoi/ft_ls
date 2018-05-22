/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 04:30:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 23:28:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void		lstdel_head(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head)->next;
	free((*head)->name);
	free((*head)->path);
	free((*head)->user_name);
	free((*head)->group_name);
	free(*head);
	(*head) = tmp;
}

t_fileinfo	*lstpop(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}

void		lstdel_one(t_fileinfo *to_del)
{
	free(to_del->name);
	free(to_del->path);
	free(to_del->user_name);
	free(to_del->group_name);
	free(to_del);
}
