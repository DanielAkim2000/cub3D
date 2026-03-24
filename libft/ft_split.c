/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:10:54 by rbourdon          #+#    #+#             */
/*   Updated: 2025/11/08 20:50:24 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	ret;
	int	in_word;
	int	i;

	in_word = 0;
	ret = 0;
	i = 0;
	while (s[i])
	{
		if (in_word == 0 && s[i] != c)
		{
			ret++;
			in_word = 1;
		}
		if (in_word == 1 && s[i] == c)
			in_word = 0;
		i++;
	}
	return (ret);
}

static void	*ft_free_all(char **s, int index)
{
	while (index-- > 0)
		free(s[index]);
	free(s);
	return (NULL);
}

static int	ft_word_len(char const *s, char c, int index)
{
	int	ret;

	ret = 0;
	while (s[index + ret] && s[index + ret] != c)
		ret++;
	return (ret);
}

static char	*ft_strndup(char const *s, char c, int index)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = ft_word_len(s, c, index);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len && s[index + i])
	{
		ret[i] = s[index + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**ret;
	int		index;

	if (!s)
		return (NULL);
	ret = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			ret[i++] = ft_strndup(s, c, index);
			if (!ret[i - 1])
				return (ft_free_all(ret, i - 1));
			index += ft_word_len(s, c, index);
		}
		else
			index++;
	}
	ret[i] = NULL;
	return (ret);
}
