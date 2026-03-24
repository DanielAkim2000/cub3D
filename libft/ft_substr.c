/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:46:38 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 22:34:29 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			real_len;
	unsigned int	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		ret = malloc(1);
		if (!ret)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	real_len = 0;
	while (s[real_len + start] && real_len < len)
		real_len++;
	ret = (char *)malloc((real_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < real_len)
		ret[i] = s[start + i];
	ret[i] = '\0';
	return (ret);
}
