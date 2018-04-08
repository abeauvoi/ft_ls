/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 20:21:29 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:54:58 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step			integer_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	char		str[20];
	intmax_t	nb;
	int			ndigits;
	char		sign;

	if (PREC != -1)
		FLAGS &= ~ZERO;
	if (ft_isupper(**format))
		SIZE = IS_LONG;
	get_value(ap, SIZE, &nb, SIGNED);
	sign = get_sign(nb, FLAGS);
	ndigits = (!nb && !PREC ? 0 : ftpf_itoa(ft_abs(nb), str, DEC, DIGITS));
	WIDTH -= ft_max(ndigits, PREC) + (sign ? 1 : 0);
	if (!(FLAGS & (LEFT | ZERO)))
		padding(buffer, WIDTH, ' ');
	if (sign)
		copy_to_buf(buffer, sign);
	if (PREC > ndigits)
		padding(buffer, PREC - ndigits, '0');
	else if (FLAGS & ZERO)
		padding(buffer, WIDTH, '0');
	while (--ndigits >= 0)
		copy_to_buf(buffer, str[ndigits]);
	return (END_OF_CONVERSION);
}
