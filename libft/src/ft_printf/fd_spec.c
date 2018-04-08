/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 23:49:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:10:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		fd_spec(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)format;
	(void)spec;
	if ((buffer->fd = va_arg(*ap, int)) < 0)
		buffer->fd = 1;
	return (END_OF_CONVERSION);
}
