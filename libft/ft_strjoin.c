/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:12:43 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 22:20:02 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_moded(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy_moded(char *ret, const char *s1, int start)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		ret[start + i] = s1[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_moded(s1);
	len_s2 = ft_strlen_moded(s2);
	ret = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strcpy_moded(ret, s1, 0);
	ft_strcpy_moded(ret, s2, len_s1);
	ret[len_s1 + len_s2] = '\0';
	return (ret);
}
