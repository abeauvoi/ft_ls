/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:41:09 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/16 14:41:30 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

void		ft_gen_swap(void *a, void *b, size_t size)
{
	unsigned char	c;
	unsigned char	*ca;
	unsigned char	*cb;

	ca = (unsigned char *)a;
	cb = (unsigned char *)b;
	while (size--)
	{
		c = *ca;
		*ca = *cb;
		*cb = c;
		++ca;
		++cb;
	}
}
