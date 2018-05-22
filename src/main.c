/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:12:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 21:22:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ls.h"

int			main(int argc, const char **argv)
{
	t_ls	info;

	(void)argc;
	init(&info);
	argv += parse_options(argv, &info.options);
	argv = setup(&info, argv);
	bubble_sort_argv(argv);
	insert_command_line_args(argv, &info);
	return (core(&info, info.entries, info.dirs));
}
