/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:08:27 by rbourdon          #+#    #+#             */
/*   Updated: 2025/12/13 13:57:13 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_sign(int nb)
{
	if (nb < 0)
		write (1, "-", 1);
	else
		write (1, "+", 1);
}

int	ft_width_star(char c, t_format *format, va_list ap)
{
	if (c == '*')
	{
		format->width = va_arg(ap, int);
		return (1);
	}
	return (0);
}

int	ft_prec_star(char c, t_format *format, va_list ap)
{
	if (c == '*')
	{
		format->prec_len = va_arg(ap, int);
		return (1);
	}
	return (0);
}

int	ft_max(int len1, int len2)
{
	if (len1 > len2)
		return (len1);
	return (len2);
}
