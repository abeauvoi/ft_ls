/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_skip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:43:55 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/21 19:19:33 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			skip_spaces_and_sign(const char **s, char *const sign)
{
	while (**s && ft_isspace(**s))
		++*s;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*sign = -1;
		++*s;
	}
}

int					ft_atoi_skip(const char **s)
{
	unsigned int	acc;
	char			sign;
	unsigned int	digit;

	sign = 1;
	skip_spaces_and_sign(s, &sign);
	acc = ft_digittoint(**s);
	while (ft_isdigit(*(++(*s))))
	{
		if (acc > INT_MAX / 10)
			return (-1 * sign);
		else
		{
			digit = ft_digittoint(**s);
			acc *= 10;
			if (INT_MAX - digit < acc)
				return (-1 * sign);
			else
				acc += digit;
		}
	}
	return ((int)(acc * sign));
}
