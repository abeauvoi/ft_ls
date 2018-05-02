/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 04:46:49 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:16:34 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

void	print_blocks(t_fileinfo *entry)
{
	if (entry->stat_ok)
		ft_printf("%llu ", entry->sbuf.st_blocks);
	else
		ft_printf("%s ", "?");
}
