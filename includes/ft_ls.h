/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:21:17 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <errno.h>
# include <inttypes.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"

/*
** Macros
*/

# define FT_LS_BUFSIZ 4096
# define FILETYPE_LETTER "?pcdb-lswd"
# define FT_LS_OPTIONS "ASRailrst"
# define MAX_ERR_SIZE 47
# define ERR_FMT_A "%wError: %s -- (%c)\n"
# define FT_LS_INVALID_OPT "Invalid option"
# define MAJOR(x) ((int32_t)(((t_u32)(x) >> 24) & 0xff))
# define MINOR(x) ((int32_t)((x) & 0xffffff))

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
	ALMOST_ALL = 1,
	SIZE_SORT = 2,
	RECURSIVE = 4,
	ALL = 8,
	PRINT_INODE = 16,
	LONG_LIST = 32,
	REVERSE = 64,
	PRINT_BLOCKS = 128,
	MODIF_SORT = 256,
	OPTIONS
}				t_ls_opts;

enum			e_col_id
{
	INODE_COL,
	BLOCKS_COL,
	NLINKS_COL,
	OWNER_COL,
	GROUP_COL,
	MAJOR_DEV_COL,
	MINOR_DEV_COL,
	FILE_SIZE_COL,
	LFMT_COLS
};

# define DISPLAY_MASK (ALMOST_ALL | ALL)

struct	s_col_info
{
	bool	valid_len;
	size_t	line_len;
	size_t	*col_arr;
};

typedef struct	s_fileinfo
{
	char				*name;
	size_t				namlen;
	size_t				pathlen;
	char				*path;
	enum e_filetype		filetype;
	bool				stat_ok;
	struct stat			sbuf;
	struct passwd		*pwd;
	struct group		*grp;
	struct s_fileinfo	*next;
}				t_fileinfo;

typedef bool (*t_cmp)(t_fileinfo *, t_fileinfo *, t_ls_opts);

typedef struct	s_ls
{
	t_ls_opts		options;
	void			(*outf)(t_fileinfo *, struct s_ls);
	t_fileinfo		*dirs;
	t_fileinfo		*entries;
	t_cmp			cmpf;
	size_t			nb_args;
	char			buf[FT_LS_BUFSIZ + 1];
	char			*a;
	char			*z;
	uint8_t			long_format_col_widths[LFMT_COLS];
	ino_t			max_inode;
	blkcnt_t		max_block_size;
	nlink_t			max_nlink;
	uid_t			max_uid;
	gid_t			max_gid;
	dev_t			max_major;
	dev_t			max_minor;
	off_t			max_file_size;
}				t_ls;

/*
** Core
*/

size_t			parse_options(const char *const *argv, t_ls_opts *flags);
void			insert_command_line_args(const char *const *argv, t_ls *info);
void			init(t_ls *info);
const char		**setup(t_ls *info, const char **argv);
void			core(t_ls info, t_fileinfo *entries, t_fileinfo *dirs);
bool			display_entry(const char *arg, t_ls_opts options);
void			display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		t_ls *info);
void			add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo **tmp);
void			read_current_dir(t_ls *info, t_fileinfo **entries,
		t_fileinfo **dirs, DIR *dirp);

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
void			short_format(t_fileinfo *entry, t_ls info);

/*
** long format
*/

void			long_format(t_fileinfo *entry, t_ls info);
void			print_user(uid_t uid);
void			print_group(gid_t gid);
void			print_inode(t_fileinfo *entry);
void			print_filename(t_fileinfo *entry);
void			print_size(t_fileinfo *entry);
void			print_blocks(t_fileinfo *entry);

/*
** Utils
*/

char			*concat_path(const char *path, const char *arg, size_t len_1,
		size_t len_2);
bool			cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
bool			rev_cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
enum e_filetype	get_filetype(mode_t protection);
void			bubble_sort_argv(const char **argv);
void			bufferize_str(t_ls *info, const char *str, int len);
void			bufferize_char(t_ls *info, char c);
char			*ft_ultoa(char *ptr, unsigned long val);
char			*pad_buffer(char *ptr, size_t len);

/*
** List
*/

void			lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls info);
t_fileinfo		*lstnew(void);
t_fileinfo		*lstpop(t_fileinfo **head);
t_fileinfo		*init_node(t_fileinfo *cur_dir, struct dirent *de);
void			lstpush(t_fileinfo **head, t_fileinfo *entry);
void			lstdel_head(t_fileinfo **head, t_fileinfo **dup);

#endif
