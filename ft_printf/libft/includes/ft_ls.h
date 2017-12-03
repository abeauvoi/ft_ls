/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/11/16 18:24:00 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft_types.h"

/*
** Formatting
*/

# define MIN_COLUMN_WIDTH 3

# ifndef S_COL_INFO
#  define S_COL_INFO

struct	s_col_info
{
	t_bool	valid_len;
	size_t	line_len;
	size_t	*col_arr;
};

# endif

/*
** Error formats 
*/

# define FTLS_ERR_FMT	"%wft_ls: %s: %s\n"

/*
** Enum and structures
*/

# ifndef E_FILETYPE
#  define E_FILETYPE

enum	e_filetype
{
	UNKNOWN,
	FIFO,
	CHARDEV,
	DIRECTORY,
	BLOCKDEV,
	NORMAL,
	SYMBOLIC_LINK,
	SOCK,
	WHITEOUT,
	ARG_DIRECTORY
};
# endif
# define FILETYPE_LETTER "?pcdb-lswd"

# define FT_LS_FLAGS "ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1"

# ifndef E_FLAGS
#  define E_FLAGS

enum	e_flags
{
	ALMOST_ALL = 1 << 0,
	ONE_PER_LINE = 1 << 1,
	ALL = 1 << 2,
	REVERSE = 1 << 3,
	RECURSIVE = 1 << 4,
	MODIF_SORT = 1 << 5,
	DISPLAY_GUID = 1 << 6,
	SUPPRESS_OWNER = 1 << 7,
	COL_DISPLAY = 1 << 8,
	ACCESS_SORT = 1 << 9,
	LONG_LIST = 1 << 10,
	SIZE_SORT = 1 << 11,
	COLOR = 1 << 12
};
# endif
# ifndef E_ACL_TYPE
#  define E_ACL_TYPE

enum	e_acl_type
{
	ACL_T_NONE,
	ACL_T_LSM_CONTEXT_ONLY,
	ACL_T_YES
};
# endif

# ifndef S_FILEINFO
#  define S_FILEINFO

struct	s_fileinfo
{
	char	*name;
	char	*linkname;
	char	*absolute_name;
	enum e_filetype	filetype;
	char	*scontext;
	t_bool	stat_ok;
	t_bool	linkok;
	enum e_acl_type	acl_type;
	t_bool	has_capability;
	int	quoted;
};
# endif

# ifndef S_LS
#  define S_LS

struct	s_ls
{
	enum e_flags	flags;
};
# endif

#endif
