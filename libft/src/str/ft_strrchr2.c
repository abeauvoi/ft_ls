/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:20:18 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/19 23:59:33 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

int			ft_strrchr2(const char *const str, char c, size_t lenstr)
{
	int		i;

	i = lenstr - 1;
	while (i > 0 && str[i] != c)
		--i;
	return (i);
}
