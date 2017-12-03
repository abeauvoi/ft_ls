/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:18:16 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/10/25 19:42:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			print_short_tab(short int *data, size_t len,
		unsigned char radix)
{
	len /= sizeof(short int);
	while (len--)
	{
		ft_putnbr_base(*data++, radix);
		if (len > 0)
			ft_putchar(' ');
	}
}

static void			print_int_tab(int *data, size_t len, unsigned char radix)
{
	len /= sizeof(int);
	while (len--)
	{
		ft_putnbr_base(*data++, radix);
		if (len > 0)
			ft_putchar(' ');
	}
}

static void			print_long_tab(long int *data, size_t len,
		unsigned char radix)
{
	len /= sizeof(long);
	while (len--)
	{
		ft_putnbr_base(*data++, radix);
		if (len > 0)
			ft_putchar(' ');
	}
}

void				ft_print_int_tab_base(void *data, unsigned char size_of,
		size_t len, unsigned char radix)
{
	if (size_of == 2)
		print_short_tab((short int *)data, len, radix);
	else if (size_of == 4)
		print_int_tab((int *)data, len, radix);
	else if (size_of == 8)
		print_long_tab((long *)data, len, radix);
}
