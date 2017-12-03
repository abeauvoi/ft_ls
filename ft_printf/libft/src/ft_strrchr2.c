/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:20:18 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/01 15:24:09 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/*
** We assume end points to a null character.
*/

char		*ft_strrchr2(const char *end, int c, size_t lenstr)
{
	char	ch;

	ch = (char)c;
	while (lenstr--)
	{
		if (*(--end) == ch)
			return ((char *)end);
	}
	return (NULL);
}
