/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 20:26:21 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/28 21:44:42 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step			unsigned_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	char		str[21];
	uintmax_t	nb;
	int			ndigits;

	if (PREC != -1)
		FLAGS &= ~ZERO;
	if (ft_isupper(**format))
		SIZE = IS_LONG;
	get_value(ap, SIZE, &nb, UNSIGNED);
	ndigits = (!nb && !PREC ? 0 : ftpf_itoa(nb, str, DEC, DIGITS));
	WIDTH -= ft_max(PREC, ndigits);
	if (!(FLAGS & (LEFT | ZERO)))
		padding(buffer, WIDTH, ' ');
	if (PREC > ndigits)
		padding(buffer, PREC - ndigits, '0');
	else if (FLAGS & ZERO)
		padding(buffer, WIDTH, '0');
	while (--ndigits >= 0)
		copy_to_buf(buffer, str[ndigits]);
	return (END_OF_CONVERSION);
}
