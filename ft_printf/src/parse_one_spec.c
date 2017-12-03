/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_one_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 20:13:47 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 20:04:39 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** This table contains function pointers indexed by ascii values,
** for quick access, starting at 0 for 'space' up to 91 for 'z'
*/

static const t_ftpf_parser	g_ft_table[] =
{
	space_flag,
	unknown_form,
	unknown_form,
	alt_flag,
	unknown_form,
	percent_spec,
	unknown_form,
	group_flag,
	unknown_form,
	unknown_form,
	get_width,
	sign_flag,
	unknown_form,
	left_flag,
	get_precision,
	unknown_form,
	zero_flag,
	get_width,
	get_width,
	get_width,
	get_width,
	get_width,
	get_width,
	get_width,
	get_width,
	get_width,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	char_spec,
	integer_spec,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	integer_spec,
	unknown_form,
	unknown_form,
	long_double_mod,
	unknown_form,
	unknown_form,
	octal_spec,
	unknown_form,
	unknown_form,
	unknown_form,
	string_spec,
	unknown_form,
	unsigned_spec,
	unknown_form,
	unknown_form,
	hex_spec,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	unknown_form,
	binary_spec,
	char_spec,
	integer_spec,
	unknown_form,
	unknown_form,
	unknown_form,
	half_mod,
	integer_spec,
	intmax_mod,
	unknown_form,
	long_mod,
	unknown_form,
	unknown_form,
	octal_spec,
	pointer_spec,
	unknown_form,
	non_printable_spec,
	string_spec,
	unknown_form,
	unsigned_spec,
	unknown_form,
	fd_spec,
	hex_spec,
	unknown_form,
	size_mod,
	colors
};

/*
** This function will parse one %...abcd... conversion format specification and
** fill the spec pointer up.
** The variable step is here to determine the behavior of the function.
** step = CONTINUE == 0;
** --------------------> This is the default value that keeps the loop going.
** step = END_OF_CONVERSION == 1;
** -----------------------------> If the character is a conversion specifier
** character (e.g. aAbcCdDeEfF...), we exit the function.
** step = OUT_OF_SCOPE == 2;
** -----------------------> We copy the character without conversion.
** step = END_OF_FORMAT == 3;
** -------------------------> If we encounter a \0 in the conversion format.
*/

t_step					parse_one_spec(const char **format, va_list *ap,
		t_ftpf_info *spec, t_ftpf_buf *buffer)
{
	unsigned char		current_char;
	t_step				step;

	step = CONTINUE;
	while (step == CONTINUE)
	{
		++*format;
		current_char = (unsigned char)**format;
		if (!current_char)
			step = END_OF_FORMAT;
		else if (current_char < ' ' || current_char > '{')
			step = unknown_form(format, ap, spec, buffer);
		else
			step = g_ft_table[current_char - ' '](format, ap, spec, buffer);
	}
	return (step);
}
