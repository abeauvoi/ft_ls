/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_no_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:45:41 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/06/03 17:54:12 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp_no_case(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 && ft_tolower(*s1) == ft_tolower(*s2) && n-- > 1)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
