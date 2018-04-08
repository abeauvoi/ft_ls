/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:16:14 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/02/06 04:29:21 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include "libft.h"

/*
** Reduced pointer names
*/

# define WIDTH spec->width
# define PREC spec->prec
# define FLAGS spec->flags
# define SIZE spec->size

/*
** Digits & Padding
*/

# ifndef DIGITS
#  define DIGITS			"0123456789abcdefghijklmnopqrstuvwxyz"
# endif
# define UPPER_DIGITS	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
** Get_value modes
*/

# define SIGNED 0
# define UNSIGNED 1

/*
** Color tags
*/

# define CA "{eoc}0{bold}1{uline}4{blink}5{hl}7{hidden}8{rbold}21{ruline}24"
# define CB "{rblink}25{rhl}27{rhidden}28{black}30{red}31{green}32{yellow}33"
# define CC "{blue}34{pink}35{cyan}36{white}37{bblack}40{bred}41{bgreen}42"
# define CD "{byellow}43{bblue}44{bpink}45{bcyan}46{bwhite}47"
# define COLOR_TABLE CA CB CC CD

/*
** Typedefs
*/

typedef enum				e_step
{
	CONTINUE,
	END_OF_CONVERSION,
	OUT_OF_SCOPE,
	END_OF_FORMAT,
	DATA_IS_NULL
}							t_step;

typedef enum				e_status
{
	FAILURE = -1,
	SUCCESS
}							t_status;

enum
{
	COLOR_CODE_SIZE = 6,
	COLORS = 21,
	MAX_NDIGITS = 64,
	BUF_SIZE = 1024
}							e_limits;

typedef enum				e_ftpf_radix
{
	BIN = 2,
	OCT = 8,
	DEC = 10,
	HEX = 16
}							t_ftpf_radix;

typedef enum				e_ftpf_size
{
	IS_CHAR,
	IS_SHORT,
	IS_INT,
	IS_LONG,
	IS_LONG_DOUBLE,
	IS_SIZE_T,
	IS_INTMAX,
	SIZES
}							t_ftpf_size;

typedef enum				e_ftpf_flag
{
	ZERO = 0x0001,
	SIGN = 0x0002,
	ALT = 0x0004,
	SPACE = 0x0008,
	LEFT = 0x0010,
	UPPER = 0x0020,
	GROUP = 0x0040
}							t_ftpf_flag;

typedef int					t_wchar;
typedef	unsigned char		t_uc;

typedef struct				s_ftpf_info
{
	t_ftpf_size				size;
	t_ftpf_flag				flags;
	int						prec;
	int						width;
}							t_ftpf_info;

typedef struct				s_ftpf_buf
{
	char					start[BUF_SIZE + 1];
	char					*current;
	char					*end;
	int						fd;
	int						done;
}							t_ftpf_buf;

typedef t_step				(*t_ftpf_parser)(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
typedef void				(*t_ftpf_get_val)(va_list *ap, t_uc mode,
		void *data);

/*
** Definitions
*/

int							ft_printf(const char *format, ...);
int							ft_printf_core(const char *format, va_list *ap);

/*
** Conversion parser functions
*/

t_step						parse_one_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						colors(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						space_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						unknown_form(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						alt_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						percent_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						group_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						get_width(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						sign_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						left_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						get_precision(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						zero_flag(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						get_width(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						char_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						integer_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						long_double_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						octal_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						string_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						hex_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						binary_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						half_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						intmax_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						long_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						number_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						pointer_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						non_printable_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						string_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						unsigned_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						fd_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						hex_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						size_mod(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);
t_step						float_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer);

/*
** Argument retrieval
*/

void						get_value(va_list *ap, t_ftpf_size size,
		void *data, t_uc mode);
void						arg_is_int(va_list *ap, t_uc mode, void *data);
void						arg_is_size(va_list *ap, t_uc mode, void *data);
void						arg_is_intmax(va_list *ap, t_uc mode, void *data);

/*
** Utilities
*/

size_t						ftpf_itoa(uintmax_t nb, char *str, t_uc radix,
		const char *digits);
size_t						ftpf_ftoa(long double val, char *str, int prec);
void						init_buffer(t_ftpf_buf *buffer);
size_t						ft_wcslen(const t_wchar *s);
size_t						ft_wchar_bc(t_wchar ch);
size_t						ft_wcs_bc(const t_wchar *s, int prec);
void						wchar_to_utf8(t_ftpf_buf *buffer, t_wchar ch);
int							atoi_skip(const char **format);
void						copy_to_buf(t_ftpf_buf *buffer, const char ch);
void						safe_ft_strncpy(t_ftpf_buf *buffer,
		const char *src, ssize_t len);
void						padding(t_ftpf_buf *buffer, int stat,
		char pad_char);
char						*ft_strstrn(const char *big, const char *little,
		size_t n);
char						get_sign(intmax_t nb, t_ftpf_flag flags);
void						print_null(t_ftpf_info *spec, t_ftpf_buf *buffer);
void						flush_buffer(t_ftpf_buf *buffer, size_t len);
t_bool						ft_iswprint(t_wchar wc);

#endif
