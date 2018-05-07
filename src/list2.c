/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 04:30:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 04:20:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	lstdel_head(t_fileinfo **head, t_fileinfo **dup)
{
	t_fileinfo	*tmp;

	tmp = (*head)->next;
	free((*head)->name);
	free((*head)->path);
	free((*head)->user_name);
	free((*head)->group_name);
	free(*head);
	(*head) = tmp;
	(*dup) = tmp;
}

t_fileinfo	*lstpop(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}
