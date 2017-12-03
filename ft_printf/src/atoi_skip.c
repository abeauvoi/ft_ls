/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_skip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 17:26:00 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/04 17:31:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Description: This function retrieves an int within the format string and
** updates the format pointer.
** It handles overflowing of the acc variable.
** Returns: (int) [-1,+2147483647]
*/

int			atoi_skip(const char **format)
{
	int		acc;
	int		digit;

	acc = ft_digittoint(**format);
	while (ft_isdigit(*(++(*format))))
	{
		if (acc > INT_MAX / 10)
			acc = -1;
		else
		{
			digit = ft_digittoint(**format);
			acc *= 10;
			if (INT_MAX - digit < acc)
				acc = -1;
			else
				acc += digit;
		}
	}
	--*format;
	return (acc);
}
