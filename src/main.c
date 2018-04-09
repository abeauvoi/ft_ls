/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:12:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 09:51:52 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, const char *const *argv)
{
	t_ls	info;

	if (argc == 1)
		print_usage();
	else
	{
		++argv;
		init(&info);
		parse_argv(argv, &info.options);
		sort_argv((const char **)argv);
		setup(&info);
		test(argv, info);
	}
	return (0);
}
