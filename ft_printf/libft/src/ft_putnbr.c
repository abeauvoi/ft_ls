/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 21:33:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/20 15:54:21 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr(int nb)
{
	unsigned int	tmp;

	tmp = (nb < 0 ? -nb : nb);
	if (nb < 0)
		ft_putchar('-');
	if (tmp >= 10)
		ft_putnbr(tmp / 10);
	ft_putchar((tmp % 10) + '0');
}
