/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:52:48 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/03 02:05:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*d;

	d = dst;
	while (*src && len-- > 0)
		*d++ = *src++;
	while (len--)
		*d++ = 0;
	return (dst);
}
