/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:58:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 01:22:17 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <
#include "ft_ls.h"

char		*concat_path(const char *path, const char *arg, size_t len_1,
		size_t len_2)
{
	char	*join;

	if (!(join = ft_strnew(len_1 + len_2 + 1)))
		return (NULL);
	ft_strcpy(join, path);
	if (join[len_1 - 1] != '/')
		join[len_1++] = '/';
	ft_strcpy(join + len_1, arg); 
	return (join);
}

t_bool		file_exists(const char *path, t_file *entry)
{
	struct stat	statbuf;
	int			ret;

	if ((ret = stat(path, &statbuf)) == 0)
	{
		entry->filetype = statbuf.st_mode & S_IFMT;
		entry->linkok = S_ISLNK(statbuf.st_mode);
	}
	return (ret);
}
