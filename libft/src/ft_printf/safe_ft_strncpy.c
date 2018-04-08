/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft_strncpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 03:17:25 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/02 15:13:48 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	safe_ft_strncpy(t_ftpf_buf *buffer, const char *src, ssize_t len)
{
	while (len-- && *src)
		copy_to_buf(buffer, *src++);
}
