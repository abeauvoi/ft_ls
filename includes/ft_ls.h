/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 06:59:12 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <errno.h>
# include <inttypes.h>
# include <sys/stat.h>
# include "ft_printf.h"

/*
** Macros
*/

# define MIN_COLUMN_WIDTH 3
# define FILETYPE "?pcdb-lswd"
# define FT_LS_OPTIONS "ASRalrt"
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
	SIZE_SORT = 1U << 1,
	RECURSIVE = 1U << 2,
	ALL = 1U << 3,
	LONG_LIST = 1U << 4,
	REVERSE = 1U << 5,
	MODIF_SORT = 1U << 6,
	OPTIONS
}				t_ls_opts;

# define DISPLAY_MASK (ALMOST_ALL | ALL)

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

typedef struct	s_fileinfo
{
	t_bool	is_dup;
	const char	*name;
	size_t	namlen;
	const char	*linkname;
	const char	*path;
	enum e_filetype	filetype;
	t_bool	stat_ok;
	t_bool	linkok;
	int		errno_dup;
	enum e_acl_type	acl_type;
	struct stat	sbuf;
	struct s_fileinfo	*next;
}				t_fileinfo;

typedef struct	s_ls
{
	t_ls_opts	options;
	void		(*outf)(t_fileinfo *);
	t_fileinfo	*dirs;
	t_fileinfo	*entries;
}				t_ls;

/*
** Core
*/

size_t		parse_options(const char *const *argv, t_ls_opts *flags);
void		insert_args(const char *const *argv, t_ls *info);
void		init(t_ls *info);
void		setup(t_ls *info);
void		test(t_ls info, t_fileinfo *entries, t_fileinfo *dirs);

/*
** Error management
*/

void		ft_perror(const char *arg);
void		print_error_and_exit(const char *format, const char *s,
		const char *arg);
void		perror_and_exit(void);

/*
** Output
*/

void		print_usage(void);
void		long_format(t_fileinfo *entry);
void		short_format(t_fileinfo *entry);

/*
** Utils
*/

char		*concat_path(const char *path, const char *arg, size_t len_1,
		size_t len_2);

/*
** List
*/

void		lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls_opts options);
t_fileinfo	*lstnew(const char *name, const char *path, size_t namlen,
		t_bool is_dup);
t_fileinfo	*lstpop(t_fileinfo **head);
void		del_entry(t_fileinfo *entry);

#endif
