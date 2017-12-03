/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 00:38:56 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 19:16:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		group_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)format;
	(void)ap;
	(void)buffer;
	FLAGS |= GROUP;
	return (CONTINUE);
}
