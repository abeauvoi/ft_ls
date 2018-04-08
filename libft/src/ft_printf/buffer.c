/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 19:01:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:30:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	init_buffer(t_ftpf_buf *buffer)
{
	ft_bzero(buffer->start, buffer->current - buffer->start);
	buffer->current = buffer->start;
}

void	flush_buffer(t_ftpf_buf *buffer, size_t len)
{
	if (!len)
		return ;
	if (write(buffer->fd, buffer->start, len) == FAILURE)
	{
		buffer->done = FAILURE;
		return ;
	}
	init_buffer(buffer);
	if (buffer->done != FAILURE)
		buffer->done += len;
}

void	copy_to_buf(t_ftpf_buf *buffer, const char to_copy)
{
	if (buffer->current == buffer->end)
		flush_buffer(buffer, BUF_SIZE);
	*(buffer->current)++ = to_copy;
}

void	padding(t_ftpf_buf *buffer, int stat, char pad_char)
{
	while (stat-- > 0)
		copy_to_buf(buffer, pad_char);
}
