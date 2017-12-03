/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:29:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/10/23 19:37:59 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchrset(const char *s, const char *charset)
{
	const char	*temp;

	while (*charset)
	{
		temp = s;
		while (*temp)
		{
			if (*temp == *charset)
				return ((char *)temp);
			++temp;
		}
		++charset;
	}
	return (NULL);
}
