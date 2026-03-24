/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:47:20 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/21 09:27:53 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sign(int nb)
{
	if (nb < 0)
		return (1);
	return (0);
}

int	ft_min_len(int len1, int len2)
{
	if (len1 < len2)
		return (len1);
	return (len2);
}

int	ft_diff_or_zero(int len1, int len2)
{
	if (len1 > len2)
		return (len1 - len2);
	return (0);
}

int	ft_converter_lower_hex(unsigned int nb, char *s)
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

int	ft_converter_upper_hex(unsigned int nb, char *s)
{
	char	*hex;
	int		i;

	hex = "0123456789ABCDEF";
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
