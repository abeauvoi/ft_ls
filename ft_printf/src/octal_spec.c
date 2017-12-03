/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:16:55 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:55:18 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		alt_mod(t_ftpf_info *spec, uintmax_t nb, size_t ndigits)
{
	if (!nb && PREC <= (ssize_t)ndigits)
		PREC = 1;
	else if (nb && PREC < (ssize_t)ndigits)
		PREC = ndigits + 1;
}

t_step			octal_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	char		str[23];
	uintmax_t	nb;
	int			ndigits;

	if (PREC != -1)
		FLAGS &= ~ZERO;
	if (ft_isupper(**format))
		SIZE = IS_LONG;
	get_value(ap, SIZE, &nb, UNSIGNED);
	ndigits = (!nb && !PREC ? 0 : ftpf_itoa(nb, str, OCT, DIGITS));
	if (FLAGS & ALT)
		alt_mod(spec, nb, ndigits);
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
