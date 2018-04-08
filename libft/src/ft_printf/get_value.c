/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 21:53:13 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 19:59:26 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			arg_is_char(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = (unsigned char)va_arg(*ap, unsigned int);
	else
		*((intmax_t *)data) = (signed char)va_arg(*ap, int);
}

static void			arg_is_short(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = (unsigned short int)va_arg(*ap, unsigned int);
	else
		*((intmax_t *)data) = (short int)va_arg(*ap, int);
}

static void			arg_is_long(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = va_arg(*ap, unsigned long int);
	else
		*((intmax_t *)data) = va_arg(*ap, long int);
}

static void			arg_is_long_double(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = va_arg(*ap, unsigned long long int);
	else
		*((intmax_t *)data) = va_arg(*ap, long long int);
}

void				get_value(va_list *ap, t_ftpf_size size, void *data,
		t_uc mode)
{
	t_ftpf_get_val	array[SIZES];

	if (size == IS_INT)
		arg_is_int(ap, mode, data);
	else
	{
		array[IS_CHAR] = arg_is_char;
		array[IS_SHORT] = arg_is_short;
		array[IS_LONG] = arg_is_long;
		array[IS_LONG_DOUBLE] = arg_is_long_double;
		array[IS_SIZE_T] = arg_is_size;
		array[IS_INTMAX] = arg_is_intmax;
		array[size](ap, mode, data);
	}
}
