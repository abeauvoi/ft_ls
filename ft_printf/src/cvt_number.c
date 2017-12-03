/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvt_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:37:49 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:31:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		get_sign(intmax_t nb, t_ftpf_flag flags)
{
	char	sign;

	sign = 0;
	if (nb < 0)
		sign = '-';
	else if (flags & SPACE)
		sign = ' ';
	else if (flags & SIGN)
		sign = '+';
	return (sign);
}

size_t		ftpf_itoa(uintmax_t nb, char *str, t_uc radix, const char *digits)
{
	size_t	i;

	i = 0;
	if (nb == 0)
		str[i++] = '0';
	else
		while (nb)
		{
			str[i++] = digits[nb % radix];
			nb /= radix;
		}
	str[i] = 0;
	return (i);
}
