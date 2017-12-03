/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:39:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/10/25 19:41:50 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int			build_one_line(int fd, char *buf, t_file *file)
{
	int				n;
	char			*tmp;

	while ((n = read(fd, buf, BUFF_SIZE)))
	{
		if (!(tmp = ft_strnew(file->saved_len + n)))
			return (-1);
		ft_memcpy(tmp, file->saved, file->saved_len);
		ft_memcpy(tmp + file->saved_len, buf, n);
		free(file->saved);
		file->saved = tmp;
		file->saved_len += n;
		if (ft_memchr(buf, '\n', n))
			break ;
	}
	return (n);
}

static t_file		*get_current_file(t_hist *hist, const int fd)
{
	t_file			*p;

	if (!hist->files)
	{
		hist->files = (t_file *)malloc(sizeof(*p));
		ft_bzero(hist->files, sizeof(*(hist->files)));
		hist->files->fd = fd;
		return (hist->last_access = hist->files);
	}
	if (hist->last_access->fd == fd)
		return (hist->last_access);
	p = hist->files;
	while (p->fd != fd && p->next)
		p = p->next;
	if (p->fd == fd)
		return (p);
	p->next = (t_file *)malloc(sizeof(*p));
	ft_bzero(p->next, sizeof(*(p->next)));
	p->next->fd = fd;
	return (hist->last_access = p->next);
}

static size_t		clear_history(t_hist *hist, t_file *file, size_t index_nl,
		t_bool reached_eof)
{
	char			*p;
	t_file			*prev;

	if ((file->saved_len -= index_nl))
		--file->saved_len;
	p = (!file->saved_len ? NULL : ft_memcpy(ft_strnew(file->saved_len),
				file->saved + index_nl + 1, file->saved_len));
	free(file->saved);
	file->saved = p;
	if (reached_eof)
	{
		if ((prev = hist->files) == file)
			hist->files = (prev->next ? prev->next : NULL);
		else
			while (prev->next != file)
				prev = prev->next;
		prev->next = file->next;
		free(file);
		file = NULL;
		return (0);
	}
	return (index_nl);
}

static int			get_one_line(t_hist *hist, t_file *file, char **line,
		char *add_nl)
{
	size_t			index_nl;

	if (add_nl)
	{
		index_nl = add_nl - file->saved;
		if (!(*line = ft_memcpy(ft_strnew(index_nl), file->saved, index_nl)))
			return (-1);
		return (clear_history(hist, file, index_nl, 0));
	}
	if (!(*line = ft_memcpy(ft_strnew(file->saved_len), file->saved,
					file->saved_len)))
		return (-1);
	return (clear_history(hist, file, file->saved_len, 1));
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_hist	hist = {NULL, NULL};
	t_file			*file;
	int				n;
	char			*add_nl;

	if (fd == -1 || !line || read(fd, buf, 0) == -1)
		return (-1);
	buf[BUFF_SIZE] = 0;
	if ((file = get_current_file(&hist, fd))->saved
			&& (add_nl = ft_memchr(file->saved, '\n', file->saved_len)))
		return (get_one_line(&hist, file, line, add_nl));
	if (!(n = build_one_line(fd, buf, file)) && !file->saved)
		return (clear_history(&hist, file, file->saved_len, 1));
	add_nl = ft_memchr(file->saved, '\n', file->saved_len);
	return (get_one_line(&hist, file, line, add_nl));
}
