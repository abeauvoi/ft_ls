/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:34:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:16:16 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_ls.h"

void	print_usage(void)
{
	ft_printf("Usage: ./%{red}ft_ls%{eoc} [-%{bred}" FT_LS_OPTIONS "%{eoc}] "
			"[%{green}file ... %{eoc}]\n"
			"%{bold}See the manual for more information%{rbold}\n");
}
