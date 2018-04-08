/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdigittoint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:20:27 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/20 19:41:30 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_xdigittoint(char c)
{
	int	d;

	d = c - '0';
	if ((unsigned int)d < 10)
		return (d);
	d = c - 'a';
	if ((unsigned int)d < 6)
		return (d + 10);
	d = c - 'A';
	if ((unsigned int)d < 6)
		return (d + 10);
	return (-1);
}
