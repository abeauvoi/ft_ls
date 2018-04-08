/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:57:23 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/12 06:45:16 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static inline size_t	find_null(const char *cp, const char *str)
{
	if (cp[0] == 0)
		return (cp - str);
	if (cp[1] == 0)
		return (cp - str + 1);
	if (cp[2] == 0)
		return (cp - str + 2);
	if (cp[3] == 0)
		return (cp - str + 3);
	if (cp[4] == 0)
		return (cp - str + 4);
	if (cp[5] == 0)
		return (cp - str + 5);
	if (cp[6] == 0)
		return (cp - str + 6);
	if (cp[7] == 0)
		return (cp - str + 7);
	__builtin_unreachable();
}

size_t					ft_strlen(const char *str)
{
	const char				*char_ptr;
	const unsigned long int	*longword_ptr;
	unsigned long int		longword;
	unsigned long int		himagic;
	unsigned long int		lomagic;

	char_ptr = str;
	while (((unsigned long int)char_ptr & (sizeof(longword) - 1)) != 0)
		++char_ptr;
	if (*char_ptr == '\0')
		return (char_ptr - str);
	longword_ptr = (unsigned long int *)char_ptr;
	himagic = 0x80808080L;
	lomagic = 0x01010101L;
	himagic = (himagic << 32) | himagic;
	lomagic = (lomagic << 32) | lomagic;
	while (1)
	{
		longword = *longword_ptr++;
		if (((longword - lomagic) & himagic) != 0)
		{
			char_ptr = (const char *)(longword_ptr - 1);
			return (find_null(char_ptr, str));
		}
	}
}
