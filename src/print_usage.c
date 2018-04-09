/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:34:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 04:39:12 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_usage(void)
{
	ft_printf("Usage: ./ft_ls [-" FT_LS_OPTIONS "] [file ...]\n"
			"%{bold}See `man ls` for more info%{rbold}\n");
}
