/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:24:40 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/20 20:37:09 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_format	format_struct;
	int			len;

	i = 0;
	len = 0;
	va_start (ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			ft_reinit_format(&format_struct);
			i += ft_read_format(format + i, &format_struct, ap);
			len += ft_work_sender(ap, &format_struct);
		}
		else
		{
			write (1, &format[i], 1);
			len++;
		}
		i++;
	}
	return (va_end (ap), len);
}

int	ft_work_sender(va_list ap, t_format *format)
{
	int	len;

	len = 0;
	if (format->type == 'c')
		len += ft_print_char(va_arg(ap, int), format);
	else if (format->type == 's')
		len += ft_print_string(va_arg(ap, char *), format);
	else if (format->type == 'p')
		len += ft_print_pointer((unsigned long)va_arg(ap, void *), format);
	else if (format->type == 'i' || format->type == 'd')
		len += ft_print_integer(va_arg(ap, int), format);
	else if (format->type == 'u')
		len += ft_print_uinteger(va_arg(ap, unsigned int), format);
	else if (format->type == 'x')
		len += ft_print_lower_hex(va_arg(ap, unsigned int), format);
	else if (format->type == 'X')
		len += ft_print_upper_hex(va_arg(ap, unsigned int), format);
	else if (format->type == '%')
		len += ft_print_percent();
	return (len);
}

int	ft_get_first_flag(const char *s, t_format *format)
{
	int	i;

	i = 0;
	while (s[i] == '-' || s[i] == '+' || s[i] == '0' || s[i] == '#'
		|| s[i] == ' ')
	{
		if (s[i] == '-')
			format->left_align = 1;
		if (s[i] == '+')
			format->sign = 1;
		if (s[i] == '0')
			format->zero_spaces = 1;
		if (s[i] == '#')
			format->htag = 1;
		if (s[i] == ' ')
			format->space = 1;
		if (s[i] == '%')
			format->percent = 1;
		i++;
	}
	return (i);
}

int	ft_read_format(const char *s, t_format *format, va_list ap)
{
	int	i;

	i = 0;
	i += ft_get_first_flag(s, format);
	i += ft_width_star(s[i], format, ap);
	while (s[i] >= '0' && s[i] <= '9')
	{
		format->width = format->width * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] == '.')
	{
		format->precision = 1;
		i++;
		i += ft_prec_star(s[i], format, ap);
		while (s[i] >= '0' && s[i] <= '9')
		{
			format->prec_len = format->prec_len * 10 + (s[i] - '0');
			i++;
		}
	}
	format->type = s[i];
	return (i);
}
