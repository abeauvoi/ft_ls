/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 19:39:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/05 19:52:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_wcslen(const t_wchar *s)
{
	t_wchar	*p;

	p = (t_wchar *)s;
	while (*p)
		++p;
	return (p - s);
}
