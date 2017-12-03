/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 17:31:53 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/05/12 23:08:18 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_check_range(unsigned long acc, t_bool neg,
		unsigned int to_add)
{
	unsigned long	cutoff;
	unsigned int	cutlim;

	cutoff = (neg ? MY_LONG_MAX + 1 : MY_LONG_MAX);
	cutlim = cutoff % 10;
	cutoff /= 10;
	if (acc > cutoff || (acc == cutoff && to_add > cutlim))
		return (neg ? MY_UNDERFLOW : MY_OVERFLOW);
	return (TEST_SUCCESS);
}

int					ft_atoi(const char *s)
{
	unsigned long	acc;
	t_bool			neg;
	unsigned int	test;

	acc = 0;
	neg = FALSE;
	while (*s && ft_isspace(*s))
		++s;
	if (*s == '-' || *s == '+')
	{
		neg = (*s == '-' ? TRUE : FALSE);
		++s;
	}
	test = 0;
	while (*s && ft_isdigit(*s) && test != FT_ATOI_MAX_STRLEN)
	{
		if (test == FT_ATOI_MAX_STRLEN - 1
				&& ft_check_range(acc, neg, *s - '0') != TEST_SUCCESS)
			return (ft_check_range(acc, neg, *s - '0'));
		acc = acc * 10 + *(s++) - '0';
		++test;
	}
	return (neg ? (int)acc * -1 : (int)acc);
}
