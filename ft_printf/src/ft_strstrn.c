/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:45:47 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 18:56:17 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_strstrn(const char *big, const char *little, size_t n)
{
	const char	*l;
	const char	*b;
	size_t		i;

	if (little == NULL || !*little)
		return ((char *)big);
	while (*big)
	{
		l = little;
		if (*big == *little)
		{
			b = big;
			i = n;
			while (i-- && *b++ == *l++)
				if (!i || !*l)
					return ((char *)big);
		}
		++big;
	}
	return (NULL);
}
