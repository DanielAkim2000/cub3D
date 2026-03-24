/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:54:21 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/10 13:05:07 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;
	size_t	j;

	if (size == 0)
		return (ft_strlen(src));
	dst_size = ft_strnlen(dst, size);
	src_size = ft_strlen(src);
	i = 0;
	if (size <= dst_size)
		return (size + src_size);
	i = dst_size;
	j = 0;
	while ((i + 1 < size) && (src[j]))
	{
		dst[i] = src[j++];
		i++;
	}
	dst[i] = '\0';
	return (dst_size + src_size);
}
