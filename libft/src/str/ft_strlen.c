/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:57:23 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/20 22:48:32 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"
#include "libft_macros.h"

size_t					ft_strlen(const char *str)
{
	const char	*start;
	long		*aligned_addr;

	start = str;
	if (!_UNALIGNED(str))
	{
		aligned_addr = (long *)str;
		while (!DETECT_NULL(*aligned_addr))
			++aligned_addr;
		str = (const char *)aligned_addr;
	}
	while (*str)
		++str;
	return (str - start);
}
