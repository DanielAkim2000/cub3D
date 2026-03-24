/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:55:52 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:12:32 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;
	size_t			i;

	if (nmemb == 0 || size == 0)
	{
		ret = malloc(1);
		if (!ret)
			return (NULL);
		ret[0] = '\0';
		return ((void *)ret);
	}
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	ret = (void *)malloc(nmemb * size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		ret[i++] = 0;
	return (ret);
}
