/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 17:12:47 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/19 23:50:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char			*ft_strnstr(const char *haystack, const char *ndl, size_t len)
{
	const char	*n;
	const char	*h;
	size_t		i;

	n = ndl;
	if (*ndl == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (*haystack == *n)
		{
			h = haystack;
			i = len;
			while (i-- && *h++ == *n++)
				if (!*n)
					return ((char *)haystack);
		}
		--len;
		++haystack;
		n = ndl;
	}
	return (NULL);
}
