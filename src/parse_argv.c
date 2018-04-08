/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/08 23:14:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_argv(const char *const *argv, const char *optstring,
		uint64_t *options)
{
	int		i;
	char	*arg;
	char	*tmp;

	while (*argv)
	{
		arg = (char*)*argv;
		if (arg[0] == '-')
		{
			++arg;
			while (*arg)
			{
				i = 0;
				while (optstring[i++])
				{
					if ((tmp = ft_strchr(optstring, *arg)) != NULL)
						*options |= (1U << (tmp - optstring));
					else
						print_error_and_exit(ERR_FMT_A, FT_LS_INVALID_OPT, arg);
				}
				++arg;
			}
		}
		++argv;
	}	
}
