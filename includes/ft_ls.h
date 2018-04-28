/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/28 07:37:28 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <errno.h>
# include <inttypes.h>
# include <sys/stat.h>
# include <dirent.h>
# include "ft_printf.h"

/*
** Macros
*/

# define MIN_COLUMN_WIDTH 3
# define FILETYPE "?pcdb-lswd"
# define FT_LS_OPTIONS "ASRalrt"
# define MAX_ERR_SIZE 47
# define ERR_FMT_A "%wError: %s -- (%c)\n"
# define FT_LS_INVALID_OPT "Invalid option"
# define MAJOR(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x) ((int32_t)((x) & 0xffffff))
# define STRINGIFY(x) #x
# define LENGTH(x) (sizeof(STRINGIFY(x)) - 1)

/*
** Typedefs, Enum and Structs
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
	bool	valid_len;
	size_t	line_len;
	size_t	*col_arr;
};

typedef struct	s_fileinfo
{
	const char	*name;
	size_t	namlen;
	size_t	pathlen;
	const char	*linkname;
	const char	*path;
	enum e_filetype	filetype;
	bool	stat_ok;
	int		errno_dup;
	struct stat	sbuf;
	struct s_fileinfo	*next;
}				t_fileinfo;

typedef bool (*t_cmp)(t_fileinfo *, t_fileinfo *, t_ls_opts);

typedef struct	s_ls
{
	t_ls_opts	options;
	void		(*outf)(t_fileinfo *);
	t_fileinfo	*dirs;
	t_fileinfo	*entries;
	t_cmp		cmpf;
	size_t		nb_dirs;
}				t_ls;

/*
** Core
*/

size_t			parse_options(const char *const *argv, t_ls_opts *flags);
void			insert_command_line_args(const char *const *argv, t_ls *info);
void			init(t_ls *info);
const char		**setup(t_ls *info, const char **argv);
void			test(t_ls info, t_fileinfo *entries, t_fileinfo *dirs);

/*
** Error management
*/

void			ft_perror(const char *arg);
void			print_error_and_exit(const char *format, const char *s,
			const char *arg);
void			perror_and_exit(void);

/*
** Output
*/

void			print_usage(void);
void			long_format(t_fileinfo *entry);
void			short_format(t_fileinfo *entry);

/*
** Utils
*/

char			*concat_path(const char *path, const char *arg, size_t len_1,
		size_t len_2);
bool			cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
bool			rev_cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
enum e_filetype	get_filetype(mode_t protection);
void			bubble_sort_argv(const char **argv);

/*
** List
*/

void			lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls info);
t_fileinfo		*lstnew(void);
t_fileinfo		*lstpop(t_fileinfo **head);
t_fileinfo		*init_node(t_fileinfo *cur_dir, struct dirent *de);
void			lstpush(t_fileinfo **head, t_fileinfo *entry);
void			lstdel_head(t_fileinfo **head);

#endif
