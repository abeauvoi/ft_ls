/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:26:19 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/27 04:06:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *list, t_list *(*f)(t_list *elem))
{
	t_list	*lstmap;

	lstmap = NULL;
	while (list)
	{
		ft_lstpush(&lstmap, f(list));
		list = list->next;
	}
	return (lstmap);
}
