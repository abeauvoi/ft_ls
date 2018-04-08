/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:12:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/08 23:15:27 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char *argv[])
{
	t_ls	info;

	if (argc == 1)
		ft_printf("Usage: ./ft_ls -options <arg0> <arg1> ...\n"
				"Options:\n"
				"--------\n"
				"\t-a: Show hidden files\n"
				"\t-r: Reserve lexicographical sort\n"
				"\t-R: Recursively access subdirectories\n"
				"\t-l: Long format\n"
				"\t-t: Time sort\n");
	else
	{
		parse_argv((const char *const *)argv, FT_LS_OPTIONS, &info.options); 
		ft_printf("Optstring:%s\nOptions:%.64b\n", FT_LS_OPTIONS, info.options);
	}
	return (0);
}
