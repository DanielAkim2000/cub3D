/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintegers_worker1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:09:01 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 13:34:12 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uinteger(unsigned int nb, t_format *format)
{
	int	len;
	int	k;

	len = ft_uint_size(nb);
	if (nb == 0)
		len = 1;
	format->diff_prec_len = format->prec_len - len;
	format->diff_width_prec = ft_diff_or_zero(format->width, format->prec_len);
	if (format->left_align)
		ft_print_uinteger_laligned(nb, len, format);
	else
		ft_print_uinteger_normal(nb, len, format);
	k = ft_max(format->width, format->prec_len);
	if (format->precision && format->prec_len == 0
		&& !format->width && (len == 0 || nb == 0))
		return (0);
	return (ft_max(k, len));
}

void	ft_print_uinteger_laligned(unsigned int nb, int len, t_format *format)
{
	int	k;

	if (format->precision && format->prec_len == 0 && nb == 0)
		return (ft_spaces_filler(format->width));
	if (format->prec_len > len)
		ft_zero_filler(format->prec_len - len);
	ft_special_putuint_fd(format, nb, 1);
	if (format->diff_prec_len < 0)
		k = format->width - len - format->sign;
	else
		k = format->width - len - format->sign - format->diff_prec_len;
	ft_spaces_filler(k);
}

void	ft_print_uinteger_normal(unsigned int nb, int len, t_format *format)
{
	if (format->precision && format->prec_len == 0 && nb == 0)
		return (ft_spaces_filler(format->width));
	else if (format->precision)
	{
		if (format->prec_len > len)
		{
			if (format->width > format->prec_len)
				ft_spaces_filler(format->diff_width_prec);
			ft_zero_filler(format->diff_prec_len);
		}
		else
			ft_spaces_filler(format->width - len);
	}
	else
		ft_print_uinteger_normal_noprec(len, format);
	ft_special_putuint_fd(format, nb, 1);
}

void	ft_print_uinteger_normal_noprec(int len, t_format *format)
{
	if (format->width > len)
	{
		if (format->zero_spaces)
			ft_zero_filler(format->width - len);
		else
			ft_spaces_filler(format->width - len);
	}
	else
		ft_spaces_filler(format->width - len);
}
