/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_macros.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <abeauvoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 05:06:59 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/01/15 05:15:11 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MACROS_H
# define LIBFT_MACROS_H

# define MY_LONG_MAX 9223372036854775807UL
# define MY_OVERFLOW -1
# define MY_UNDERFLOW 0
# define TEST_SUCCESS 2
# define NO_INPUT -1
# define DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"
# define FT_ATOI_MAX_STRLEN 20
# define TO_DIGIT(x) ((unsigned int)(x) - '0')
# define IS_DIGIT(x) (TO_DIGIT(x) <= 9)
# define IS_ALPHA(x) (('A' <= (x) && (x) <= 'Z') || ('a' <= (x) && (x) <= 'z'))
# define IS_ALNUM(x) (IS_DIGIT(x) || IS_ALPHA(x))

#endif
