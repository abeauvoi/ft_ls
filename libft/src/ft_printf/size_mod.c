/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 19:01:26 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:31:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_step		half_mod(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (spec->size == IS_INT)
		spec->size = IS_SHORT;
	else if (spec->size == IS_SHORT)
		spec->size = IS_CHAR;
	return (CONTINUE);
}

t_step		long_mod(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (spec->size == IS_INT)
		spec->size = IS_LONG;
	else if (spec->size == IS_LONG)
		spec->size = IS_LONG_DOUBLE;
	return (CONTINUE);
}

t_step		size_mod(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (spec->size == IS_INT)
		spec->size = IS_SIZE_T;
	return (CONTINUE);
}

t_step		intmax_mod(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (spec->size == IS_INT)
		spec->size = IS_INTMAX;
	return (CONTINUE);
}

t_step		long_double_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	(void)buffer;
	(void)format;
	(void)ap;
	if (spec->size == IS_INT)
		spec->size = IS_LONG_DOUBLE;
	return (CONTINUE);
}
