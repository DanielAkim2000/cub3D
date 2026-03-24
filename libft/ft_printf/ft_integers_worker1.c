/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integers_worker1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:04:07 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 13:27:26 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_integer(int nb, t_format *format)
{
	int	len;
	int	k;
	int	fs;

	k = 0;
	ft_print_integer_helper(format, &len, nb);
	if (format->left_align)
		ft_print_integer_laligned(nb, len, format);
	else
	{
		ft_print_integer_normal(nb, len, format);
		ft_special_putnbr_fd(format, nb, 1);
	}
	if (format->space && nb >= 0 && format->sign == 0)
		len++;
	if (ft_spaceflag_return_handler(format, nb, len) == 1)
		format->sign = 1;
	fs = format->sign;
	k = ft_max_len(format->width, format->prec_len + fs, len);
	if (format->precision && format->prec_len == 0
		&& !format->width && (len == 0 || nb == 0))
		return (0);
	return (ft_max(k, len + format->sign));
}

void	ft_print_integer_normal(int nb, int len, t_format *format)
{
	ft_spaceflag_handler(format, nb);
	if (format->precision && format->prec_len == 0 && nb == 0)
		return (ft_spaces_filler(format->width));
	else if (format->precision)
	{
		if (format->prec_len > len)
		{
			if (format->width > format->prec_len)
				ft_spaces_filler(format->diff_width_prec - format->sign);
			if (format->sign || nb < 0)
				ft_print_sign(nb);
			ft_zero_filler(format->diff_prec_len);
		}
		else
		{
			ft_spaces_filler(format->width - len - format->sign);
			if (format->sign || nb < 0)
				ft_print_sign(nb);
		}
	}
	else
		ft_print_integer_normal_noprec(nb, len, format);
}

void	ft_print_integer_normal_noprec(int nb, int len, t_format *format)
{
	if (format->width > len)
	{
		if (format->zero_spaces)
		{
			if (format->sign || nb < 0)
			{
				ft_print_sign(nb);
				format->sign_done = 1;
			}
			ft_zero_filler(format->width - len - format->sign);
		}
		else
			ft_spaces_filler(format->width - len - format->sign);
	}
	else
		ft_spaces_filler(format->width - len - format->sign);
	if ((format->sign || nb < 0) && format->sign_done == 0)
		ft_print_sign(nb);
}

void	ft_print_integer_laligned(int nb, int len, t_format *format)
{
	if (format->precision && format->prec_len == 0 && nb == 0)
		return (ft_spaces_filler(format->width));
	if (format->sign || nb < 0)
		ft_print_sign(nb);
	ft_zero_filler(format->diff_prec_len);
	ft_special_putnbr_fd(format, nb, 1);
	if (format->width > len + format->sign)
	{
		if (format->prec_len < len)
			ft_spaces_filler(format->width - len - format->sign);
		else
			ft_spaces_filler(format->diff_width_prec - format->sign);
	}
}
