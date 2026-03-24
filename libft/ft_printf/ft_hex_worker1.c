/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_worker1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:06:46 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 09:27:24 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_lower_hex(unsigned int nb, t_format *format)
{
	int		i;

	format->ret_hex = (char *)malloc(32 * sizeof(char));
	if (!format->ret_hex)
		return (0);
	i = ft_converter_lower_hex(nb, format->ret_hex);
	format->len_hex = (int)ft_strlen(format->ret_hex);
	if (format->precision)
		format->diff_prec_len = format->prec_len - format->len_hex;
	if (format->left_align)
		ft_print_lhex_laligned(nb, i, format);
	else
		ft_print_lhex_normal(nb, i, format);
	free(format->ret_hex);
	if (format->precision && format->prec_len == 0 && nb == 0
		&& format->width < format->len_hex)
		return (0);
	return (ft_max_len(format->len_hex, format->width, format->prec_len));
}

int	ft_print_upper_hex(unsigned int nb, t_format *format)
{
	int		i;

	format->ret_hex = (char *)malloc(32 * sizeof(char));
	if (!format->ret_hex)
		return (0);
	i = ft_converter_upper_hex(nb, format->ret_hex);
	format->len_hex = (int)ft_strlen(format->ret_hex);
	if (format->precision)
		format->diff_prec_len = format->prec_len - format->len_hex;
	if (format->left_align)
		ft_print_uhex_laligned(nb, i, format);
	else
		ft_print_uhex_normal(nb, i, format);
	free(format->ret_hex);
	return (ft_max_len(format->len_hex, format->width, format->prec_len));
}

void	ft_print_lhex_laligned(unsigned int nb, int i, t_format *format)
{
	if (format->htag && nb != 0)
		ft_htag_handler(format);
	if (nb == 0 && format->precision && format->prec_len == 0)
		format->len_hex = 0;
	if (format->prec_len > format->len_hex)
		ft_zero_filler(format->prec_len - format->len_hex);
	if ((nb == 0 && !format->precision) || (nb == 0 && format->prec_len > 0))
		write(1, "0", 1);
	if (nb != 0)
		while (--(i) >= 0)
			write(1, &format->ret_hex[i], 1);
	ft_hex_spaces_handler(format);
}

void	ft_print_lhex_normal(unsigned int nb, int i, t_format *format)
{
	if (nb == 0 && format->precision && format->prec_len == 0)
		format->len_hex = 0;
	if (format->htag && nb != 0)
		ft_htag_handler(format);
	if (format->precision)
	{
		ft_hex_spaces_handler(format);
		if (format->prec_len > format->len_hex)
			ft_zero_filler(format->prec_len - format->len_hex);
	}
	else if (format->zero_spaces)
		ft_zero_filler(format->width - format->len_hex);
	else
		ft_hex_spaces_handler(format);
	if (format->htag && nb != 0)
		write(1, "0x", 2);
	if ((nb == 0 && !format->precision) || (nb == 0 && format->prec_len > 0))
		write(1, "0", 1);
	if (nb != 0)
		while (--(i) >= 0)
			write(1, &format->ret_hex[i], 1);
}

void	ft_print_uhex_laligned(unsigned int nb, int i, t_format *format)
{
	if (format->htag && nb != 0)
		ft_htag_handler(format);
	if (nb == 0 && format->precision && format->prec_len == 0)
		format->len_hex = 0;
	if (format->prec_len > format->len_hex)
		ft_zero_filler(format->prec_len - format->len_hex);
	if (!(format->precision && format->prec_len == 0 && nb == 0))
		while (--i >= 0)
			write(1, &format->ret_hex[i], 1);
	ft_hex_spaces_handler(format);
}
