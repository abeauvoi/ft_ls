/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 17:44:30 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/14 13:25:39 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_isspace(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	return (ch == 32 || ch == 12 || ch == 10 || ch == 13 || ch == 9
			|| ch == 11);
}