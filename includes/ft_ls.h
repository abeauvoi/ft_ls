/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:13:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 00:27:36 by abeauvoi         ###   ########.fr       */
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

# define FT_LS_BUFSIZ 8192
# define FILETYPE_LETTER "?pcdb-lsw"
# define FT_LS_OPTIONS "AFGSRailrst"
# define MAX_ERR_SIZE 47
# define DISPLAY_MASK (ALMOST_ALL | ALL)
# define ERR_FMT_A "%wError: %s -- (%c)\n"
# define FT_LS_INVALID_OPT "Invalid option"
# define MAJOR(x) ((int32_t)(((t_u32)(x) >> 24) & 0xff))
# define MINOR(x) ((int32_t)((x) & 0xffffff))
# define SIX_MONTHS_IN_SECONDS (31556952 >> 1)
# define RESET_COLOR "[m"

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
	SOCKET,
	WHITEOUT
};

typedef enum	e_options
{
	ALMOST_ALL = 1,
	FILETYPE_INDICATOR = 2,
	FILENAME_COLOR = 4,
	SIZE_SORT = 8,
	RECURSIVE = 16,
	ALL = 32,
	PRINT_INODE = 64,
	LONG_LIST = 128,
	REVERSE = 256,
	PRINT_BLOCKS = 512,
	MODIF_SORT = 1024,
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

enum			e_color_index
{
	NO_COLOR = -1,
	COLOR_DIR,
	COLOR_LINK,
	COLOR_SOCK,
	COLOR_FIFO,
	COLOR_EXEC,
	COLOR_BDEV,
	COLOR_CDEV,
	COLOR_EXEC_SETUID,
	COLOR_EXEC_SETGID,
	COLOR_DIR_OTH_S,
	COLOR_DIR_OTH_NO_S,
	COLOR_INDEXES
};

typedef struct	s_fileinfo
{
	char				*name;
	char				*user_name;
	int					ctab_index;
	size_t				user_name_length;
	size_t				group_name_length;
	char				*group_name;
	size_t				namlen;
	size_t				pathlen;
	char				*path;
	enum e_filetype		filetype;
	bool				stat_ok;
	struct stat			sbuf;
	struct s_fileinfo	*next;
}				t_fileinfo;

typedef bool	(*t_cmp)(t_fileinfo *, t_fileinfo *, t_ls_opts);

/*
** The longest possible ansi escape sequence generated by get_colors is :
** [1;xx;xxm == 10
*/

typedef struct	s_ls
{
	t_ls_opts		options;
	void			(*outf)(t_fileinfo *, struct s_ls *);
	t_fileinfo		*dirs;
	t_fileinfo		*entries;
	t_cmp			cmpf;
	size_t			nb_args;
	char			buf[FT_LS_BUFSIZ + 1];
	char			ctab[COLOR_INDEXES][10 + 1];
	size_t			len_color[COLOR_INDEXES];
	char			*a;
	char			*z;
	bool			colored_output;
	bool			found_major_minor_dev;
	uint8_t			lfmt_cwidth[LFMT_COLS];
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
int				core(t_ls *info, t_fileinfo *entries, t_fileinfo *dirs);
bool			display_entry(const char *arg, t_ls_opts options);
void			display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		t_ls *info);
void			add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo *tmp);
void			read_current_dir(t_ls *info, t_fileinfo **entries,
		t_fileinfo **dirs, DIR *dirp);
void			print_dir_name(t_ls *info, const char *path, size_t pathlen);

/*
** Error management
*/

void			ft_perror(const char *arg, size_t arglen, t_ls *info);
void			print_error_and_exit(const char *format, const char *s,
			const char *arg);
void			perror_and_exit(void);

/*
** Output
*/

void			print_usage(void);
void			short_format(t_fileinfo *entry, t_ls *info);

/*
** Long format
*/

void			long_format(t_fileinfo *entry, t_ls *info);
char			*print_user(t_fileinfo *entry, char *bufp, uint8_t max_width);
char			*print_group(t_fileinfo *entry, char *bufp, uint8_t max_width);
char			*print_inode(t_fileinfo *entry, char *bufp, uint8_t max_width);
char			*print_filename(t_fileinfo *entry, char *bufp, t_ls info);
char			*print_size(t_fileinfo *entry, char *bufp, t_ls info);
char			*print_blocks(t_fileinfo *entry, char *bufp, uint8_t max_width);
char			*print_nlinks(t_fileinfo *entry, char *bufp, uint8_t max_width);
char			*print_time_info(t_fileinfo *entry, char *bufp);
char			get_others_exec_rights(mode_t mode);

/*
** Utils
*/

char			*concat_path(const char *path, const char *filename,
		size_t path_len, size_t filename_len);
bool			cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
bool			rev_cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options);
enum e_filetype	get_filetype(mode_t mode);
void			bubble_sort_argv(const char **argv);
void			strtobuf(t_ls *info, const char *str, int len);
void			chartobuf(t_ls *info, char c);
char			*ft_ultoa(char *ptr, unsigned long val, bool is_negative);
char			*pad_buffer(char *ptr, size_t len);
char			get_filetype_indicator(bool stat_ok, mode_t mode,
		enum e_filetype type);
char			*itob(char *mbuf, uintmax_t value, int max_width,
		bool is_negative);
int				numstrlen(intmax_t n);
void			save_col_widths(t_ls *info);
char			*ft_strcpy_non_printable_chars(char *dst, const char *src);
int				get_color_table_index(mode_t mode);
void			ft_ls_flush_buffer(t_ls *info);

/*
** List
*/

void			lstinsert(t_fileinfo **head, t_fileinfo *entry, t_ls info);
t_fileinfo		*lstnew(void);
t_fileinfo		*lstpop(t_fileinfo **head);
t_fileinfo		*init_node(t_fileinfo *cur_dir, struct dirent *de,
		t_ls info);
void			lstpush(t_fileinfo **head, t_fileinfo *entry);
void			lstdel_head(t_fileinfo **head);
void			lstdel_one(t_fileinfo *to_del);

/*
** Colors
*/

void			get_colors(t_ls *info);
char			*ft_strcpy_color(char *bufp, const char *color, size_t len);

#endif
