/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 20:49:21 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 23:58:51 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*new;

	if (!(new = (char *)malloc(sizeof(*new) * (size + 1))))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
