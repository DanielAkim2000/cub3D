/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:56:42 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/22 15:44:03 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*data = NULL;
	char		*ret;
	char		*buffer;
	ssize_t		b_read;
	size_t		len_data;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (free(data), data = NULL, NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	len_data = gnl_strlen(data);
	b_read = ft_reader(fd, &data, buffer, &len_data);
	if (ft_strchr_mod(data) >= 0)
	{
		ret = ft_line_handler(data, ft_strchr_mod(data));
		if (!ret)
			return (free(buffer), free(data), data = NULL, NULL);
		data = ft_data_keeper(data, ft_strchr_mod(data));
	}
	else if (b_read == 0)
		return (free(buffer), ft_eof_handler(&data));
	else
		return (free(data), data = NULL, free(buffer), NULL);
	return (free(buffer), ret);
}

ssize_t	ft_reader(int fd, char **data, char *buffer, size_t *len_data)
{
	char	*tmp;
	ssize_t	b_read;
	size_t	len;
	size_t	len_ref;
	int		nl_found;

	ft_var_init(&b_read, &len, &nl_found);
	while (!nl_found && b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
			return (b_read);
		buffer[b_read] = '\0';
		if (ft_strchr_mod(buffer) >= 0)
			nl_found = 1;
		len_ref = len;
		tmp = ft_strj(*data, buffer, &len, *len_data);
		if (!tmp)
			return (free(*data), *data = NULL, -1);
		if (len_ref != len)
			free(*data);
		*data = tmp;
		*len_data = *len_data + (size_t)b_read;
	}
	return (b_read);
}

void	ft_var_init(ssize_t *b_read, size_t *len, int *nl_found)
{
	*b_read = 1;
	*len = 0;
	*nl_found = 0;
}

char	*ft_strj(const char *s1, const char *s2, size_t *len, size_t datal)
{
	int		totsize;
	char	*ret;
	int		i;

	totsize = datal + gnl_strlen(s2);
	if (*len == 0 || *len < (size_t)(totsize + 1))
	{
		ret = (char *)malloc((totsize + 1) * 10 * sizeof(char));
		*len = (totsize + 1) * 10;
	}
	else
		ret = (char *)s1;
	if (!ret || !s2)
		return (NULL);
	i = -1;
	if (s1 && *len == (size_t)((totsize + 1) * 10))
		while (s1[++i])
			ret[i] = s1[i];
	i = -1;
	while (s2[++i])
		ret[i + datal] = s2[i];
	ret[totsize] = '\0';
	return (ret);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			real_len;
	unsigned int	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= gnl_strlen(s))
	{
		ret = malloc(1);
		if (!ret)
			return (NULL);
		return (ret[0] = '\0', ret);
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
