/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:24:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/27 04:31:32 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char		*trim;
	size_t		len;

	while (*s && ft_isblank(*s))
		++s;
	len = ft_strlen(s) - 1;
	while (ft_isblank(s[len]))
		--len;
	return (!(trim = ft_strnew(len + 1)) ? NULL : ft_strncpy(trim, s, len));
}
