/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:20:39 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/10 13:06:49 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	size_t	i;

	if (!big && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	n = 0;
	i = 0;
	while (big[n] && n < len)
	{
		i = 0;
		while (big[n + i] == little[i] && little[i] && n + i < len)
			i++;
		if (!little[i])
			return ((char *)(big + n));
		n++;
	}
	return (NULL);
}
