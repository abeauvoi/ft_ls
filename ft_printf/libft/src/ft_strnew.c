/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 20:49:21 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/21 16:29:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*new;

	if (!(new = (char *)malloc(sizeof(*new) * (size + 1))))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
