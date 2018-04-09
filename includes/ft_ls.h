/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 09:50:16 by abeauvoi         ###   ########.fr       */
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
# define FILETYPE "pcdb-ls"
# define FT_LS_OPTIONS "ARalrt"
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
	ALMOST_ALL = 1U,
	RECURSIVE = 1U << 1,
	ALL = 1U << 2,
	LONG_LIST = 1U << 3,
	REVERSE = 1U << 4,
	MODIF_SORT = 1U << 5,
	OPTIONS
}				t_ls_opts;

# define DISPLAY_MASK (ALMOST_ALL | ALL)
# define SORT_MASK (REVERSE | MODIF_SORT)

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
	void		(*outf)(const char *);
}				t_ls;

/*
** Core
*/

void		parse_argv(const char *const *argv, uint64_t *flags);
void		sort_argv(const char **argv);
void		init(t_ls *info);
void		setup(t_ls *info);
void		test(const char *const *argv, t_ls info);

/*
** Error management
*/

void		ft_perror(const char *arg);
void		print_error_and_exit(const char *format, const char *s,
		const char *arg);

/*
** Output
*/

void		print_usage(void);
void		long_format(const char *arg);
void		short_format(const char *arg);

#endif
