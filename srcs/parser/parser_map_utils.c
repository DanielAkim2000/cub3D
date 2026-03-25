/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:30:44 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/24 21:56:33 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_map_name_checker(char *s)
{
	int			len;

	if (!s)
		return (ft_error_only("Map path is NULL"), 0);
	len = ft_strlen(s);
	if (len < 5 || ft_strncmp(s + len - 4, ".cub", 4) != 0)
		return (ft_error_only("Map must have .cub extension"), 0);
	return (1);
}

int	ft_map_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	ft_map_width(char **map)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (map && map[i])
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	ft_is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D' || c == 'T');
}

int	ft_is_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_is_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}
