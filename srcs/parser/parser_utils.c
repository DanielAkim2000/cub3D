/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:10:28 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 21:22:59 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_skip_blank(const char *s, int *i)
{
	while (s[*i] && ft_is_blank(s[*i]))
		(*i)++;
}

int	ft_is_blank(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_split_identifier_value(const char *line, char **id, char **value)
{
	int	i;
	int	start;

	*id = NULL;
	*value = NULL;
	i = 0;
	while (line[i] && ft_is_blank(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_is_blank(line[i]))
		i++;
	*id = ft_substr(line, start, i - start);
	while (line[i] && ft_is_blank(line[i]))
		i++;
	*value = ft_special_strtrim(line + i, " \t\n\v\f\r");
	if (!*id || !*value || **value == '\0')
	{
		free(*id);
		free(*value);
		*id = NULL;
		*value = NULL;
		return (0);
	}
	return (1);
}

int	ft_str_isdigit(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

void	ft_blank_parser(char *line, int *i)
{
	if (!line)
		return ;
	while (line[*i] && ft_is_blank(line[*i]))
		(*i)++;
}
