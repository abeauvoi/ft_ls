/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 13:02:32 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:58:11 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void		init_spec(t_ftpf_info *spec)
{
	ft_bzero(spec, sizeof(t_ftpf_info));
	spec->prec = -1;
	spec->size = IS_INT;
}

static int		exit_ft_printf(t_ftpf_buf *buffer, va_list *ap)
{
	flush_buffer(buffer, buffer->current - buffer->start);
	va_end(*ap);
	return (buffer->done);
}

int				ft_printf_core(const char *format, va_list *ap)
{
	t_ftpf_info	spec;
	t_ftpf_buf	buffer;

	ft_bzero(buffer.start, BUF_SIZE + 1);
	buffer.current = buffer.start;
	buffer.end = buffer.start + BUF_SIZE;
	buffer.done = 0;
	buffer.fd = 1;
	while (*format)
	{
		init_spec(&spec);
		while (*format && *format != '%')
			copy_to_buf(&buffer, *format++);
		if (!*format ||
				parse_one_spec(&format, ap, &spec, &buffer) == END_OF_FORMAT)
			return (exit_ft_printf(&buffer, ap));
		if (spec.flags & LEFT)
			padding(&buffer, spec.width, ' ');
		if (buffer.done == FAILURE)
			return (FAILURE);
		++format;
	}
	return (exit_ft_printf(&buffer, ap));
}
