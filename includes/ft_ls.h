/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/08 23:16:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <errno.h>
# include <inttypes.h>
# include "ft_printf.h"

/*
** Macros 
*/

# define MIN_COLUMN_WIDTH 3
# define FILETYPE_LETTER "?pcdb-lswd"
# define FT_LS_OPTIONS "larRt"
# define ERR_FMT_A "%wError: %s -- (%c)\n"
# define FT_LS_INVALID_OPT "Invalid option"

/*
** Enum and structures
*/

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

typedef enum	e_options
{
	ALMOST_ALL = 1,
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
}				t_ls_opts;

enum	e_acl_type
{
	ACL_T_NONE,
	ACL_T_LSM_CONTEXT_ONLY,
	ACL_T_YES
};

struct	s_col_info
{
	t_bool	valid_len;
	size_t	line_len;
	size_t	*col_arr;
};

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

typedef struct	s_ls
{
	uint64_t	options;
}				t_ls;

void		print_error_and_exit(const char *format, const char *s,
		const char *arg);
void		parse_argv(const char *const *argv, const char *optstring,
		uint64_t *options);

#endif
