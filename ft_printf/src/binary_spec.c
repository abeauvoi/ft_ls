/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:07:46 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:55:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step			binary_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	char		str[65];
	uintmax_t	nb;
	int			ndigits;

	(void)format;
	if (PREC != -1)
		FLAGS &= ~ZERO;
	get_value(ap, SIZE, &nb, UNSIGNED);
	ndigits = (nb || PREC != 0 ? ftpf_itoa(nb, str, BIN, DIGITS) : 0);
	WIDTH -= ft_max(ndigits, PREC);
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
