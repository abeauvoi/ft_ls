/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 22:36:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:32:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_step	wcs_spec(const t_wchar *data, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	size_t		bytes;

	if (!data)
		return (DATA_IS_NULL);
	bytes = ft_wcs_bc(data, PREC);
	WIDTH -= bytes;
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	while (bytes)
	{
		bytes -= ft_wchar_bc(*data);
		wchar_to_utf8(buffer, *data++);
	}
	return (END_OF_CONVERSION);
}

static t_step	body(const char *data, t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	size_t		len;

	if (!data)
		return (DATA_IS_NULL);
	len = (PREC == -1 ? ft_strlen(data) : ft_min(ft_strlen(data), PREC));
	WIDTH -= len;
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	safe_ft_strncpy(buffer, data, len);
	return (END_OF_CONVERSION);
}

t_step			string_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	t_step		step;

	if (ft_isupper(**format) || SIZE == IS_LONG)
		step = wcs_spec(va_arg(*ap, const t_wchar *), spec, buffer);
	else
		step = body(va_arg(*ap, const char *), spec, buffer);
	if (step == DATA_IS_NULL)
		print_null(spec, buffer);
	return (END_OF_CONVERSION);
}
