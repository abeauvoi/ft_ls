/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:35:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/20 18:29:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmap(char const *s, char (*f)(char))
{
	char			*new;
	unsigned int	i;

	if (!s || !f || !(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*s)
		new[i++] = f(*s++);
	return (new);
}
