/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:43:30 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/18 17:32:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	if (!(new = (char *)malloc((ft_strlen(s1) + 1) * sizeof(*new))))
		return (NULL);
	i = 0;
	while ((new[i++] = *s1++) != 0)
		;
	return (new);
}
