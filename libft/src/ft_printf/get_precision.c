/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:02:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:50:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		get_precision(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	++*format;
	if (**format == '*')
	{
		if ((PREC = va_arg(*ap, int)) < 0)
			PREC = -1;
	}
	else if (ft_isdigit(**format))
		PREC = atoi_skip(format);
	else if (**format == '$')
		return (unknown_form(format, ap, spec, buffer));
	else
	{
		PREC = 0;
		--*format;
	}
	return (CONTINUE);
}
