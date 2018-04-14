/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:12:54 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/14 02:05:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	show_dirs(t_fileinfo *dirs)
{
	while (dirs)
	{
		ft_printf("name:%s\n", dirs->name);
		dirs = dirs->next;
	}
}

int			main(int argc, const char *const *argv)
{
	t_ls	info;

	(void)argc;
	init(&info);
	argv += parse_options(argv, &info.options);
	setup(&info);
	insert_command_line_args(argv, &info);
	show_dirs(info.dirs);
	return (0);
}
