/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 21:10:20 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/27 06:29:02 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TYPES_H
# define LIBFT_TYPES_H

# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_str
{
	char	*s;
	size_t	l;
}					t_str;

typedef unsigned char	t_u8;
typedef unsigned short 	t_u16;
typedef unsigned int	t_u32;

#endif
