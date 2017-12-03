/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:54:46 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/29 18:48:25 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define MY_LONG_MAX 9223372036854775807UL
# define MY_OVERFLOW -1
# define MY_UNDERFLOW 0
# define TEST_SUCCESS 2
# define FT_ATOI_MAX_STRLEN 20
# include <limits.h>
# include <string.h>
# include <stdint.h>
# include "libft_types.h"
# include "get_next_line.h"
# define NO_INPUT -1

# define DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"

/*
** Math related
*/

long				ft_pow(int nb, unsigned int pow);
uintmax_t			ft_abs(intmax_t i);

/*
** Misc.
*/

int					ft_atoi(const char *s);
int					ft_atoi_skip(const char **s);
void				ft_bzero(void *str, size_t count);
int					ft_digittoint(char c);
void				ft_delcontent(void *content, size_t content_size);
void				ft_error(char *error_msg);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
char				*ft_itoa(int n);
int					ft_isxdigit(int c);
void				ft_swap_int(int *a, int *b);

/*
** Linked lists
*/

void				ft_lstadd(t_list **alst, t_list *new_elem);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void *content, size_t content_size);
void				ft_lstiter(t_list *list, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *list, t_list *(*f)(t_list *elem));
void				ft_lstpush(t_list **alst, t_list *new_elem);
size_t				ft_lstsize(t_list *list);
t_list				*ft_lststrsplit(const char *s, char c);
void				ft_lstprint_base(t_list *list,
		unsigned char size_of_content, unsigned char radix);

/*
** Memory mgmt
*/

void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t cnt);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t count);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t count);
void				*ft_memset(void *dst, int c, size_t count);

/*
** Output
*/

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_base(long int nb, unsigned char base);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *str);
void				ft_putstr_fd(char const *s, int fd);
void				ft_print_int_tab_base(void *data, unsigned char size_of,
		size_t len, unsigned char radix);

/*
** String manipulation
*/

void				ft_revstr(char *s);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strchrnul(const char *s, int c);
void				ft_strclr(char *s);
char				*ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *dst, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strncmp_no_case(const char *s1, const char *s2,
		size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *hstk, const char *ndl, size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);

/*
** Char conversion
*/

int					ft_tolower(int c);
int					ft_toupper(int c);

#endif
