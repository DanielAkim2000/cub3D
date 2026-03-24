/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_worker2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:13:28 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/19 09:13:50 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c, t_format *format)
{
	char	ret;

	ret = (char)c;
	if (format->left_align)
	{
		write(1, &ret, 1);
		if (format->width > 1)
			ft_spaces_filler(format->width - 1);
	}
	else
	{
		if (format->width > 1)
			ft_spaces_filler(format->width - 1);
		write(1, &ret, 1);
	}
	return (ft_max_len(1, format->width, format->prec_len));
}

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}
