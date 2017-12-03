/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown_form.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 19:14:26 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:37:15 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step	unknown_form(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)ap;
	--WIDTH;
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	copy_to_buf(buffer, **format);
	return (END_OF_CONVERSION);
}
