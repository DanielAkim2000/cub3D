/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_special_trim.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:39:00 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:22:54 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	ft_pass_begin_set(char const *s1, char const *set)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (set[i] && s1[ret])
	{
		if (set[i] == s1[ret])
		{
			ret++;
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

static int	ft_before_end_set(char const *s1, char const *set)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s1[ret])
		ret++;
	if (ret == 0)
		return (-1);
	ret--;
	while (ret >= 0 && set[i] && s1[ret])
	{
		if (set[i] == s1[ret])
		{
			ret--;
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

static char	*ft_strdup_mode(char const *s, int mode)
{
	int		i;
	char	*ret;

	i = 0;
	if (mode == 1)
	{
		while (s[i])
			i++;
		ret = (char *)malloc((i + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		i = 0;
		while (s[i])
		{
			ret[i] = s[i];
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	ret = (char *)malloc(sizeof(char));
	if (!ret)
		return (NULL);
	return (ret[0] = '\0', ret);
}

char	*ft_special_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ret;
	int		i;
	int		start;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup_mode(s1, 1));
	if (s1[0] == '\0')
		return (ft_strdup_mode(s1, 0));
	start = ft_pass_begin_set(s1, set);
	len = ft_before_end_set(s1, set) - start + 1;
	if (start > ft_before_end_set(s1, set))
		return (ft_strdup_mode(s1, 0));
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s1[start + i];
		i++;
	}
	return (ret[i] = '\0', ret);
}
