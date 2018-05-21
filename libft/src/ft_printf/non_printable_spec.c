/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 22:44:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 05:27:04 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_step	body(const char *data, t_ftpf_info *spec, t_ftpf_buf *buffer,
		const char *digits)
{
	size_t		len;

	if (!data)
		return (DATA_IS_NULL);
	len = (PREC == -1 ? ft_strlen(data) : ft_min(ft_strlen(data), PREC));
	WIDTH -= len;
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	while (len--)
	{
		if (!ft_isprint(*data))
		{
			copy_to_buf(buffer, '\\');
			copy_to_buf(buffer, digits[33]);
			copy_to_buf(buffer, digits[(*data >> 4) & 0xF]);
			copy_to_buf(buffer, digits[*data & 0xF]);
		}
		else
			copy_to_buf(buffer, *data);
		++data;
	}
	return (END_OF_CONVERSION);
}

static t_step	non_wprintable_spec(const t_wchar *data, t_ftpf_info *spec,
		t_ftpf_buf *buffer, const char *digits)
{
	size_t	len;

	if (!data)
		return (DATA_IS_NULL);
	len = ft_wcs_bc(data, PREC);
	WIDTH -= len;
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	while (len)
	{
		len -= ft_wchar_bc(*data);
		if (!ft_iswprint(*data))
		{
			copy_to_buf(buffer, '\\');
			copy_to_buf(buffer, 'u');
			copy_to_buf(buffer, digits[*data & 0xf0]);
			copy_to_buf(buffer, digits[*data & 0xf]);
		}
		else
			wchar_to_utf8(buffer, *data);
		++data;
	}
	return (END_OF_CONVERSION);
}

t_step			non_printable_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	t_step		step;

	(void)format;
	if (SIZE == IS_LONG)
		step = non_wprintable_spec(va_arg(*ap, const t_wchar *), spec, buffer,
				DIGITS);
	else
		step = body(va_arg(*ap, const char *), spec, buffer, DIGITS);
	if (step == DATA_IS_NULL)
		print_null(spec, buffer);
	return (END_OF_CONVERSION);
}
