/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:39:03 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/11 20:09:57 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*find_end_of_tag(const char *format, size_t max_len)
{
	while (*format && *format != '}' && max_len--)
		++format;
	return ((char *)format);
}

t_step			colors(const char **format, va_list *ap, t_ftpf_info *spec,
		t_ftpf_buf *buffer)
{
	const char	*colors;
	char		*color_code;
	char		*end_of_tag;
	size_t		len;

	(void)ap;
	(void)spec;
	colors = COLOR_TABLE;
	if (*(end_of_tag = find_end_of_tag(*format, 8)) == '}')
	{
		len = end_of_tag - *format;
		if (!(color_code = ft_strstrn(colors, *format, len)))
			return (OUT_OF_SCOPE);
		color_code += len + 1;
		copy_to_buf(buffer, '\e');
		copy_to_buf(buffer, '[');
		copy_to_buf(buffer, *color_code++);
		if (ft_isdigit(*color_code))
			copy_to_buf(buffer, *color_code);
		copy_to_buf(buffer, 'm');
		*format += len;
		return (END_OF_CONVERSION);
	}
	return (OUT_OF_SCOPE);
}
