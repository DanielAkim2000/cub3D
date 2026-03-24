/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:07:52 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/18 16:48:58 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reinit_format(t_format *format)
{
	format->type = '0';
	format->left_align = 0;
	format->sign = 0;
	format->width = 0;
	format->zero_spaces = 0;
	format->htag = 0;
	format->space = 0;
	format->precision = 0;
	format->prec_len = 0;
	format->len_hex = 0;
	format->ret_hex = NULL;
	format->diff_prec_len = 0;
	format->diff_width_prec = 0;
	format->percent = 0;
	format->sign_done = 0;
}

void	ft_spaces_filler(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write (1, " ", 1);
		i++;
	}
}

int	ft_max_len(int len1, int len2, int len3)
{
	if (len1 >= len2 && len1 >= len3)
		return (len1);
	if (len2 >= len1 && len2 >= len3)
		return (len2);
	return (len3);
}

void	ft_zero_filler(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write (1, "0", 1);
		i++;
	}
}

int	ft_integer_size(int nb)
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
