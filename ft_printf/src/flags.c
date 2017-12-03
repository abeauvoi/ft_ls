/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:48:19 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:53:33 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		alt_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	FLAGS |= ALT;
	return (CONTINUE);
}

t_step		zero_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (!(FLAGS & LEFT))
		FLAGS |= ZERO;
	return (CONTINUE);
}

t_step		sign_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (FLAGS & SPACE)
		FLAGS &= ~SPACE;
	FLAGS |= SIGN;
	return (CONTINUE);
}

t_step		space_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (!(FLAGS & SIGN))
		FLAGS |= SPACE;
	return (CONTINUE);
}

t_step		left_flag(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (FLAGS & ZERO)
		FLAGS &= ~ZERO;
	FLAGS |= LEFT;
	return (CONTINUE);
}
