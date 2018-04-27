/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 17:31:53 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/27 06:31:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static const char	*prelim_check(const char *s, bool *neg)
{
	while (ft_isspace(*s))
		++s;
	if (*s == '-')
	{
		*neg = true;
		++s;
	}
	else if (*s == '+')
		++s;
	return (s);
}

int					ft_atoi(const char *s)
{
	bool			neg;
	unsigned int	acc;
	unsigned int	digit;

	neg = false;
	s = prelim_check(s, &neg);
	if (!((acc = TO_DIGIT(*s)) <= 9))
		return (0);
	while ((digit = TO_DIGIT(*++s)) <= 9)
	{
		if (acc > INT_MAX / 10)
			return (-1);
		else
		{
			acc *= 10;
			if (INT_MAX - digit < acc)
				return (-1);
			else
				acc += digit;
		}
	}
	if (neg)
		acc = ~acc + 1;
	return ((int)acc);
}
