/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_worker2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:25:21 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 09:27:45 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_uhex_normal(unsigned int nb, int i, t_format *format)
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
		write(1, "0X", 2);
	if (!(format->precision && format->prec_len == 0 && nb == 0))
		while (--i >= 0)
			write(1, &format->ret_hex[i], 1);
}
