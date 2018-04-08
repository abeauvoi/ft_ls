/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:45:08 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/07/05 16:58:32 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_len(const char *s, char c)
{
	return (*s && *s != c ? ft_word_len(++s, c) + 1 : 0);
}

t_list			*ft_lststrsplit(const char *s, char c)
{
	t_list		*lst;
	size_t		i;
	size_t		word_len;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		word_len = ft_word_len(s + i, c);
		ft_lstpush(&lst, ft_lstnew(ft_strsub(s, i, word_len), word_len));
		while (s[i] && s[i] != c)
			++i;
	}
	return (lst);
}
