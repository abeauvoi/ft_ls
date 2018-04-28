/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 04:30:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/28 04:34:32 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	lstdel_head(t_fileinfo **head)
{
	t_fileinfo	*tmp;

	tmp = (*head)->next;
	free((void*)(*head)->name);
	free((void*)(*head)->linkname);
	free((void*)(*head)->path);
	free(*head);
	(*head) = tmp;
}
