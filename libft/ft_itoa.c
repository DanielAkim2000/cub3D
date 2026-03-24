/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:48:28 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:19:36 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_number_len(long n)
{
	long	ret;

	ret = 1;
	while (n / 10)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

static char	*ft_convert(long len, long neg, long nb)
{
	char	*ret;

	if (nb == 0)
	{
		ret = (char *)malloc(2 * sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	ret = (char *)malloc((len + 1 + neg) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len + neg] = '\0';
	while (nb)
	{
		ret[--len + neg] = (nb % 10) + '0';
		nb /= 10;
	}
	if (neg)
		ret[0] = '-';
	return (ret);
}

char	*ft_itoa(int n)
{
	long	len;
	long	nb;
	long	neg;

	nb = n;
	neg = 0;
	if (nb < 0)
	{
		nb = -nb;
		neg = 1;
	}
	len = ft_number_len(nb);
	return (ft_convert(len, neg, nb));
}
