/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointers_worker1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:14:14 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/20 21:14:23 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(unsigned long nb, t_format *format)
{
	int		i;
	char	*ret;
	int		len;

	if (nb == 0 && format->left_align)
		return (ft_print_string_nil_lalign(format));
	else if (nb == 0 && !format->left_align)
		return (ft_print_string_nil_normal(format));
	ret = (char *)malloc(17 * sizeof(char));
	if (!ret)
		return (0);
	i = ft_lconverter_lower_hex(nb, ret);
	len = 2 + (int)ft_strlen((const char *)ret);
	if (format->left_align)
		ft_print_pointer_laligned(ret, len, format, i);
	else
		ft_print_pointer_normal(ret, len, format, i);
	free(ret);
	return (ft_max_len(len, format->width, 0));
}

void	ft_print_pointer_laligned(char *s, int len, t_format *format, int i)
{
	write(1, "0x", 2);
	if (i == 0)
		return ;
	while (--i >= 0)
		write(1, &s[i], 1);
	if (format->width > len)
		ft_spaces_filler(format->width - len);
}

void	ft_print_pointer_normal(char *s, int len, t_format *format, int i)
{
	if (format->width > len)
		ft_spaces_filler(format->width - len);
	write(1, "0x", 2);
	if (i == 0)
		return ;
	while (--i >= 0)
		write(1, &s[i], 1);
}

int	ft_print_string_nil_lalign(t_format *format)
{
	if (!format->precision || format->prec_len > 4)
	{
		write(1, "(nil)", 5);
		ft_spaces_filler(format->width - 5);
		return (ft_max_len(format->width, 5, 0));
	}
	ft_spaces_filler(ft_max_len(format->width, format->prec_len, 0));
	return (ft_max_len(format->width, format->prec_len, 0));
}

int	ft_print_string_nil_normal(t_format *format)
{
	if (!format->precision || format->prec_len > 4)
	{
		ft_spaces_filler(format->width - 5);
		write(1, "(nil)", 5);
		return (ft_max_len(format->width, 5, 0));
	}
	return (0);
}
