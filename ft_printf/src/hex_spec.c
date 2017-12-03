/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:33:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:55:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		add_prefix(t_ftpf_buf *buffer, const char *digits, t_bool alt)
{
	if (alt)
	{
		copy_to_buf(buffer, '0');
		copy_to_buf(buffer, digits[33]);
	}
}

t_step			hex_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	char		str[17];
	t_bool		alt;
	int			ndigits;
	uintmax_t	nb;
	char		*digits;

	if (PREC != -1)
		FLAGS &= ~ZERO;
	digits = (ft_isupper(**format) ? UPPER_DIGITS : DIGITS);
	get_value(ap, SIZE, &nb, UNSIGNED);
	if ((alt = nb && FLAGS & ALT))
		WIDTH -= 2;
	ndigits = (!nb && !PREC ? 0 : ftpf_itoa(nb, str, HEX, digits));
	WIDTH -= ft_max(PREC, ndigits);
	if (!(FLAGS & (LEFT | ZERO)))
		padding(buffer, WIDTH, ' ');
	add_prefix(buffer, digits, alt);
	if (PREC > ndigits)
		padding(buffer, PREC - ndigits, '0');
	else if (FLAGS & ZERO)
		padding(buffer, WIDTH, '0');
	while (--ndigits >= 0)
		copy_to_buf(buffer, str[ndigits]);
	return (END_OF_CONVERSION);
}
