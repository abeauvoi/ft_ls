/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 23:53:21 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/21 18:54:53 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_strchr2(const char *const str, char c)
{
	const char	*s;

	s = str;
	while (*s)
	{
		if (*s == c)
			return (s - str);
		++s;
	}
	return (-1);
}