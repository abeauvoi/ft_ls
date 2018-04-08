/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:57:31 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/12 06:45:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <inttypes.h>
#include "libft.h"

static void	ft_u64toa_base(uint64_t value, unsigned int base, char *buffer)
{
	char	temp[65];
	char	*p;

	p = temp;
	temp[64] = 0;
	*p++ = DIGITS[value % base];
	while ((value /= base) > 0)
		*p++ = DIGITS[value % base];
	while (p != temp)
		*buffer++ = *--p;
	*buffer = '\0';
}

char		*ft_itoa_base(int64_t n, unsigned int base)
{
	char		*buffer;
	uint64_t	uval;

	if (base < 2 || base > 16)
		return (NULL);
	uval = (uint64_t)n;
	buffer = (char *)malloc(65);
	if (n < 0 && base == 10)
	{
		*buffer++ = '-';
		uval = ~uval + 1;
	}
	ft_u64toa_base(uval, base, buffer);
	if (n < 0)
		--buffer;
	return (buffer);
}
