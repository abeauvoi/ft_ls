/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 22:17:53 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:30:26 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		arg_is_int(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = va_arg(*ap, unsigned int);
	else
		*((intmax_t *)data) = va_arg(*ap, int);
}

void		arg_is_size(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = va_arg(*ap, size_t);
	else
		*((intmax_t *)data) = va_arg(*ap, ssize_t);
}

void		arg_is_intmax(va_list *ap, t_uc mode, void *data)
{
	if (mode == UNSIGNED)
		*((uintmax_t *)data) = va_arg(*ap, uintmax_t);
	else
		*((intmax_t *)data) = va_arg(*ap, intmax_t);
}
