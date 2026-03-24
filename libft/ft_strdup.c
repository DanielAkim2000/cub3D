/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:12:01 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:51:40 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s[j])
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
