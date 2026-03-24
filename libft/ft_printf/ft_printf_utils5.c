/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:14:35 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 13:25:46 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_htag_handler_uhex_laligned(t_format *format)
{
	if (format->prec_len > format->width)
		format->prec_len = format->prec_len + 2;
	format->len_hex = format->len_hex + 2;
	write(1, "0X", 2);
	if (format->prec_len > format->len_hex)
		ft_zero_filler(format->prec_len - format->len_hex);
	else
		ft_zero_filler(format->prec_len + 2 - format->len_hex);
}

int	ft_lconverter_lower_hex(unsigned long nb, char *s)
{
	char	*hex;
	int		i;

	hex = "0123456789abcdef";
	i = 0;
	if (nb == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		return (1);
	}
	while (nb)
	{
		s[i] = hex[nb % 16];
		nb /= 16;
		i = i + 1;
	}
	s[i] = '\0';
	return (i);
}

void	ft_spaceflag_handler(t_format *format, int nb)
{
	if (format->space && nb >= 0 && !format->sign)
		write (1, " ", 1);
}

int	ft_spaceflag_return_handler(t_format *format, int nb, int len)
{
	if (format->space && nb >= 0 && !format->sign
		&& (format->prec_len > len || format->width > len)
		&& format->prec_len >= format->width)
		return (1);
	return (0);
}

void	ft_print_integer_helper(t_format *format, int *len, int nb)
{
	if (nb < 0)
		format->sign = 1;
	*len = ft_integer_size(nb);
	format->diff_prec_len = ft_diff_or_zero(format->prec_len, *len);
	format->diff_width_prec = ft_diff_or_zero(format->width, format->prec_len);
}
