/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	ft_store_texture(t_game *game, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		game->tex_paths[0] = ft_strdup(path);
	else if (ft_strncmp(id, "SO", 3) == 0)
		game->tex_paths[1] = ft_strdup(path);
	else if (ft_strncmp(id, "WE", 3) == 0)
		game->tex_paths[2] = ft_strdup(path);
	else if (ft_strncmp(id, "EA", 3) == 0)
		game->tex_paths[3] = ft_strdup(path);
	else if (ft_strncmp(id, "D", 2) == 0)
		game->tex_paths[4] = ft_strdup(path);
	else
		return (0);
	return (1);
}

static int	ft_parse_texture_line(t_game *game, char *line)
{
	char	**split;
	char	*trimmed;
	char	*path;

	trimmed = ft_strtrim(line, " \t\n");
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split || !split[0] || !split[1] || split[2])
		return (ft_free_split(&split), 0);
	path = ft_strtrim(split[1], " \t\n\r");
	if (!ft_store_texture(game, split[0], path))
		return (free(path), ft_free_split(&split), 0);
	free(path);
	ft_free_split(&split);
	return (1);
}

static int	ft_parse_color(char *line, int *color)
{
	char	**split;
	int		rgb[3];
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(line + 1, " \t\n");
	split = ft_split(trimmed, ',');
	free(trimmed);
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (ft_free_split(&split), 0);
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_free_split(&split), 0);
	}
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	ft_free_split(&split);
	return (1);
}

static int	ft_parse_element_line(t_game *game, char *line, int *count)
{
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
		|| line[0] == 'E' || line[0] == 'D')
	{
		if (!ft_parse_texture_line(game, line))
			return (0);
		if (line[0] != 'D')
			(*count)++;
		return (1);
	}
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (line[0] == 'F' && !ft_parse_color(line, &game->floor_color))
			return (0);
		if (line[0] == 'C' && !ft_parse_color(line, &game->ceil_color))
			return (0);
		(*count)++;
		return (1);
	}
	return (0);
}

int	ft_parse_elements(t_game *game, int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (ft_putstr_fd("Error\nMissing elements\n", 2), 0);
		if (line[0] == '\n' || ft_str_is_space(line))
		{
			free(line);
			continue ;
		}
		if (!ft_parse_element_line(game, line, &count))
			return (free(line), ft_putstr_fd("Error\nInvalid element\n", 2), 0);
		free(line);
	}
	return (1);
}
