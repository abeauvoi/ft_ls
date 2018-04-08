/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:04:09 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:24:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step	get_width(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	if (**format == '*')
		spec->width = va_arg(*ap, int);
	else if (ft_isdigit(**format))
		spec->width = atoi_skip(format);
	if (spec->width < 0)
	{
		spec->flags |= LEFT;
		spec->width = -spec->width;
	}
	return (CONTINUE);
}
