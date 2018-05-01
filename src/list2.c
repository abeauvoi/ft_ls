/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 04:30:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/01 05:37:14 by abeauvoi         ###   ########.fr       */
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
	free(*head);
	(*head) = tmp;
	(*dup) = tmp;
}
