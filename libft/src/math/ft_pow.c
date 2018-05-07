/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:31:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/06 20:09:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_pow(int base, unsigned int exponent)
{
	long	result;

	if (exponent == 0)
		return (1);
	result = 1;
	while (exponent-- > 0)
		result *= base;
	return (result);
}
