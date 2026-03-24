/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:18:35 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/22 15:34:47 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

ssize_t	ft_strchr_mod(const char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_line_handler(char *data, int index)
{
	char	*ret;

	ret = gnl_substr(data, 0, index + 1);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*ft_data_keeper(char *data, int index)
{
	char	*ret;

	ret = gnl_substr(data, index + 1, gnl_strlen(data) - (index + 1));
	free(data);
	if (!ret || ret[0] == '\0')
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*ft_eof_handler(char **data)
{
	char	*ret;

	if (!*data || (*data)[0] == 0)
		return (free(*data), *data = NULL, NULL);
	ret = gnl_substr(*data, 0, gnl_strlen(*data));
	if (!ret)
		return (free(*data), *data = NULL, NULL);
	free(*data);
	*data = NULL;
	return (ret);
}
