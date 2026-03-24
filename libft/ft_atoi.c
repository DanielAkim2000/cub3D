/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:25:19 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:25:41 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;
	int	i;

	sign = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = 1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	ret = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret *= 10;
		ret += (nptr[i++] - '0');
	}
	if (sign)
		return (-ret);
	return (ret);
}
