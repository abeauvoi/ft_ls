/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:17:41 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/10/03 21:45:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_base(t_list *list, unsigned char size_of_content,
		unsigned char radix)
{
	if (!list)
		return ;
	else
		while (list)
		{
			if (size_of_content == 1)
				ft_putstr((char *)list->content);
			else
				ft_print_int_tab_base(list->content, size_of_content,
						list->content_size, radix);
			ft_putchar('\n');
			list = list->next;
		}
}
