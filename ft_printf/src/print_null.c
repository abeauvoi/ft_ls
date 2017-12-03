/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_null.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:55:44 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/10 18:04:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_null(t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	if (PREC == -1)
		PREC = 6;
	WIDTH -= ft_min(6, PREC);
	if (!(FLAGS & LEFT))
		padding(buffer, WIDTH, (FLAGS & ZERO ? '0' : ' '));
	safe_ft_strncpy(buffer, "(null)", PREC);
}
