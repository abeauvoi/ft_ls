/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:17:20 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/19 23:32:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*d;

	d = dst;
	while (*d)
		++d;
	while (n--)
		if (!(*d++ = *src++))
			return (dst);
	*d = 0;
	return (dst);
}
