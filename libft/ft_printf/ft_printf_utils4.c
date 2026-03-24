/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:06:21 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/20 17:15:30 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_special_putuint_fd(t_format *format, unsigned int nb, int fd)
{
	char	c;

	if (format->precision && format->prec_len == 0 && nb == 0)
		return ;
	if (nb < 10)
	{
		c = nb + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}

int	ft_uint_size(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_htag_handler(t_format *format)
{
	if (format->prec_len > format->width)
		format->prec_len = format->prec_len + 2;
	format->len_hex = format->len_hex + 2;
}

void	ft_htag_handler_lhex_laligned(t_format *format)
{
	if (format->prec_len > format->width)
		format->prec_len = format->prec_len + 2;
	format->len_hex = format->len_hex + 2;
	write(1, "0x", 2);
	if (format->prec_len > format->len_hex)
		ft_zero_filler(format->prec_len - format->len_hex);
	else
		ft_zero_filler(format->prec_len + 2 - format->len_hex);
}

void	ft_hex_spaces_handler(t_format *format)
{
	int	k;

	k = ft_max(format->prec_len, format->len_hex);
	if (format->precision && format->width >= format->prec_len
		&& format->prec_len != 0)
		ft_spaces_filler(format->width - k);
	else if (format->precision && format->width <= format->prec_len
		&& format->prec_len != 0)
		ft_spaces_filler(format->width - k);
	else
	{
		if (format->width > format->len_hex)
			ft_spaces_filler(format->width - format->len_hex);
	}
}
