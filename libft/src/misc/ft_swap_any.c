/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:41:09 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/15 05:21:58 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

void		ft_swap_any(void *a, void *b, size_t size)
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
