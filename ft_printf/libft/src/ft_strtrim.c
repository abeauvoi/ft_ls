/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:24:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/20 19:44:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	ft_isblank(int c)
{
	return (c == 9 || c == 10 || c == 32 ? TRUE : FALSE);
}

char			*ft_strtrim(char const *s)
{
	char		*trim;
	size_t		len;

	if (!s)
		return (NULL);
	while (*s && ft_isblank(*s))
		++s;
	if (!(len = ft_strlen(s)))
		return (ft_strnew(len));
	while (ft_isblank(s[--len]))
		;
	++len;
	if (!(trim = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(trim, s, len));
}
