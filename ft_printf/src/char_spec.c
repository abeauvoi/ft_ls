/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:21:16 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 19:58:00 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		char_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	t_wchar	wc;

	if (ft_isupper(**format) || spec->size >= IS_LONG)
	{
		wc = va_arg(*ap, t_wchar);
		WIDTH -= ft_wchar_bc(wc);
		if (!(FLAGS & LEFT))
			padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
		wchar_to_utf8(buffer, wc);
	}
	else
	{
		--WIDTH;
		if (!(FLAGS & LEFT))
			padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
		copy_to_buf(buffer, (char)va_arg(*ap, int));
	}
	return (END_OF_CONVERSION);
}
