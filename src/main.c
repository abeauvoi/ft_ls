/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:12:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 06:34:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, const char *const *argv)
{
	t_ls	info;

	(void)argc;
	init(&info);
	argv += parse_options(argv, &info.options);
	setup(&info, argv);
	insert_command_line_args(argv, &info);
	test(info, info.entries, info.dirs);
	return (0);
}
