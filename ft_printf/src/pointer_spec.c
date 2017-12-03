/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:35:18 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:46:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step			pointer_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	char		str[17];
	int			ndigits;
	uintmax_t	nb;

	(void)format;
	nb = (uintmax_t)va_arg(*ap, void *);
	ndigits = (!nb && !PREC ? 0 : ftpf_itoa(nb, str, HEX, DIGITS));
	WIDTH -= ndigits + 2;
	if (!(FLAGS & (LEFT | ZERO)))
		padding(buffer, WIDTH, ' ');
	copy_to_buf(buffer, '0');
	copy_to_buf(buffer, 'x');
	if (PREC > ndigits)
		padding(buffer, PREC - ndigits, '0');
	else if (FLAGS & ZERO)
		padding(buffer, WIDTH, '0');
	while (--ndigits >= 0)
		copy_to_buf(buffer, str[ndigits]);
	return (END_OF_CONVERSION);
}
