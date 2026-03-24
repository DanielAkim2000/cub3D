/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_worker1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:11:54 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 13:34:01 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *s, t_format *format)
{
	int	i;
	int	len;

	i = 0;
	if (!s)
	{
		if (format->left_align)
			return (ft_print_string_null_lalign(format));
		else
			return (ft_print_string_null_normal(format));
	}
	if (format->precision)
		len = ft_min_len((int)ft_strlen((const char *)s), format->prec_len);
	else
		len = (int)ft_strlen((const char *)s);
	if (format->left_align)
		ft_print_string_laligned(len, s, format, &i);
	else
		ft_print_string_normal(len, s, format, &i);
	if (format->width > len)
		return (format->width);
	else
		return (len);
}

void	ft_print_string_laligned(int len, char *s, t_format *format, int *i)
{
	if (format->precision)
	{
		while (s[*i] && *i < format->prec_len)
			write (1, &s[(*i)++], 1);
	}
	else
	{
		while (s[*i])
			write (1, &s[(*i)++], 1);
	}
	if (format->width > len)
		ft_spaces_filler(format->width - len);
}

void	ft_print_string_normal(int len, char *s, t_format *format, int *i)
{
	if (format->width > len)
		ft_spaces_filler(format->width - len);
	if (format->precision)
	{
		while (s[*i] && *i < format->prec_len)
			write (1, &s[(*i)++], 1);
	}
	else
	{
		while (s[*i])
			write (1, &s[(*i)++], 1);
	}
}

int	ft_print_string_null_lalign(t_format *format)
{
	if (!format->precision || format->prec_len > 5)
	{
		write(1, "(null)", 6);
		ft_spaces_filler(format->width - 6);
		return (ft_max_len(format->width, 6, 0));
	}
	else if (format->precision)
	{
		ft_spaces_filler(format->width);
		if (format->prec_len > 5)
			return (ft_max_len(format->width, format->prec_len, 0));
		return (format->width);
	}
	return (format->width);
}

int	ft_print_string_null_normal(t_format *format)
{
	if (!format->precision || format->prec_len > 5)
	{
		ft_spaces_filler(format->width - 6);
		write(1, "(null)", 6);
		return (ft_max_len(format->width, 6, 0));
	}
	else if (format->precision)
	{
		ft_spaces_filler(format->width);
		if (format->prec_len > 5)
			return (ft_max_len(format->width, format->prec_len, 0));
		return (format->width);
	}
	return (format->width);
}
