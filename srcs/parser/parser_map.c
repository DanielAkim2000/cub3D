/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	ft_is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}

static void	ft_init_player(t_game *game, char dir, int x, int y)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	if (dir == 'N')
		game->player.dir_x = 0;
	if (dir == 'N')
		game->player.dir_y = -1;
	if (dir == 'S')
		game->player.dir_x = 0;
	if (dir == 'S')
		game->player.dir_y = 1;
	if (dir == 'E')
		game->player.dir_x = 1;
	if (dir == 'E')
		game->player.dir_y = 0;
	if (dir == 'W')
		game->player.dir_x = -1;
	if (dir == 'W')
		game->player.dir_y = 0;
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

static int	ft_parse_map_line(t_game *game, char *line, int y,
		int *player_count)
{
	int	x;

	x = -1;
	while (line[++x])
	{
		if (line[x] == '\n')
			continue ;
		if (!ft_is_valid_char(line[x]))
			return (ft_putstr_fd("Error\nInvalid char in map\n", 2), 0);
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
			|| line[x] == 'W')
		{
			ft_init_player(game, line[x], x, y);
			line[x] = '0';
			(*player_count)++;
		}
	}
	if (x > game->map_width)
		game->map_width = x;
	game->door_target[y] = ft_calloc(x + 1, sizeof(int));
	game->door_open[y] = ft_calloc(x + 1, sizeof(double));
	game->map[y] = ft_strtrim(line, "\n");
	return (1);
}

static int	ft_read_map(t_game *game, int fd, int *player_count)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && !ft_str_is_space(line)
			&& !ft_parse_map_line(game, line, y, player_count))
			return (free(line), 0);
		if (line[0] == '\n' || ft_str_is_space(line))
		{
			if (y > 0)
				break ;
		}
		else
			y++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (game->map[y] = NULL, game->door_target[y] = NULL,
		game->door_open[y] = NULL, game->map_height = y, 1);
}

int	ft_parse_map(t_game *game, int fd)
{
	int	player_count;

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
	if (!ft_read_map(game, fd, &player_count))
		return (0);
	if (player_count != 1)
		return (ft_putstr_fd("Error\nInvalid player count\n", 2), 0);
	return (1);
}
