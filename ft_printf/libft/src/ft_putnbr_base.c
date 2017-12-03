/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 21:38:38 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/21 16:10:56 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_putnbr_base(long int nb, unsigned char base)
{
	unsigned long int	tmp;
	char				*digits;

	digits = DIGITS;
	tmp = (nb < 0 ? -nb : nb);
	if (nb < 0)
		ft_putchar('-');
	if (tmp >= base)
		ft_putnbr_base(tmp / base, base);
	ft_putchar(digits[tmp % base]);
}
