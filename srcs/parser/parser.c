/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:32:02 by demane            #+#    #+#             */
/*   Updated: 2026/03/15 19:03:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_check_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	parse_texture(t_game *game, char *line)
{
	char	**split;
	char	*trimmed;
	char	*clean_path;

	trimmed = ft_strtrim(line, " \t\n");
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split || !split[0] || !split[1] || split[2])
		return (ft_free_split(&split), 0);
	clean_path = ft_strtrim(split[1], " \t\n\r");
	if (ft_strncmp(split[0], "NO", 3) == 0)
		game->tex_paths[0] = ft_strdup(clean_path);
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		game->tex_paths[1] = ft_strdup(clean_path);
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		game->tex_paths[2] = ft_strdup(clean_path);
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		game->tex_paths[3] = ft_strdup(clean_path);
	else if (ft_strncmp(split[0], "D", 2) == 0)
		game->tex_paths[4] = ft_strdup(clean_path);
	else
		return (free(clean_path), ft_free_split(&split), 0);
	free(clean_path);
	ft_free_split(&split);
	return (1);
}

static int	parse_color(char *line, int *color)
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
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E')
		{
			if (!parse_texture(game, line))
				return (free(line), 0);
			count++;
		}
		else if (line[0] == 'F' || line[0] == 'C')
		{
			if (line[0] == 'F' && !parse_color(line, &game->floor_color))
				return (free(line), 0);
			else if (line[0] == 'C' && !parse_color(line, &game->ceil_color))
				return (free(line), 0);
			count++;
		}
		else if (line[0] == 'D')
		{
			if (!parse_texture(game, line))
				return (free(line), 0);
		}
		else
			return (free(line), ft_putstr_fd("Error\nInvalid element\n", 2), 0);
		free(line);
	}
	return (1);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}

static void	init_player(t_game *game, char dir, int x, int y)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

int	ft_parse_map(t_game *game, int fd)
{
	char	*line;
	int		y;
	int		x;
	int		player_count;

	game->map = malloc(sizeof(char *) * 1000);
	if (!game->map)
		return (0);
	game->door_target = malloc(sizeof(int *) * 1000);
	if (!game->door_target)
		return (0);
	game->door_open = malloc(sizeof(double *) * 1000);
	if (!game->door_open)
		return (0);
	game->map_height = 0;
	game->map_width = 0;
	player_count = 0;
	y = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n' || ft_str_is_space(line))
		{
			free(line);
			if (y > 0)
				break ;
			continue ;
		}
		x = -1;
		while (line[++x])
		{
			if (!is_valid_char(line[x]) && line[x] != '\n')
				return (free(line), ft_putstr_fd("Error\nInvalid char in map\n",
						2), 0);
			if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
				|| line[x] == 'W')
			{
				init_player(game, line[x], x, y);
				line[x] = '0';
				player_count++;
			}
		}
		if (x > (int)game->map_width)
			game->map_width = x;
		game->door_target[y] = ft_calloc(x + 1, sizeof(int));
		game->door_open[y] = ft_calloc(x + 1, sizeof(double));
		game->map[y++] = ft_strtrim(line, "\n");
		free(line);
	}
	game->map[y] = NULL;
	game->door_target[y] = NULL;
	game->door_open[y] = NULL;
	game->map_height = y;
	if (player_count != 1)
		return (ft_putstr_fd("Error\nInvalid player count\n", 2), 0);
	return (1);
}

int	ft_check_map_closed(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == '0' || game->map[y][x] == 'D')
			{
				if (y == 0 || y == game->map_height - 1)
					return (0);
				if (x == 0 || x == (int)ft_strlen(game->map[y]) - 1)
					return (0);
				if (x >= (int)ft_strlen(game->map[y - 1]) || game->map[y
					- 1][x] == ' ')
					return (0);
				if (x >= (int)ft_strlen(game->map[y + 1]) || game->map[y
					+ 1][x] == ' ')
					return (0);
				if (game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

int	ft_parse_file(t_game *game, char *filename)
{
	int	fd;

	game->tex_paths[4] = NULL;
	game->door_target = NULL;
	game->door_open = NULL;
	if (!ft_check_extension(filename))
		return (ft_putstr_fd("Error\nInvalid file extension\n", 2), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 0);
	if (!ft_parse_elements(game, fd))
		return (close(fd), 0);
	if (!ft_parse_map(game, fd))
		return (close(fd), 0);
	close(fd);
	if (!ft_check_map_closed(game))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), 0);
	return (1);
}
