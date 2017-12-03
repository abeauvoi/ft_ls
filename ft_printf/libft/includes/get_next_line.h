/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:18:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/21 15:25:35 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# ifdef BUFF_SIZE
#  undef BUFF_SIZE
# endif
# define BUFF_SIZE 1
# define GNL_SUCCESS 1
# define GNL_EOF 0
# define GNL_ERROR -1

# define T_LIST

typedef struct s_hist	t_hist;
# define T_FILE

typedef struct s_file	t_file;

struct		s_file
{
	char	*saved;
	size_t	saved_len;
	int		fd;
	t_file	*next;
};

struct		s_hist
{
	t_file	*files;
	t_file	*last_access;
};

int			get_next_line(const int fd, char **line);

#endif
