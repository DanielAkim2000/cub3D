/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

void	ft_draw_rect_clipped(t_game *game, int rect[3], int color)
{
	int	px;
	int	py;
	int	max_x;
	int	max_y;

	max_x = MINI_OFFSET_X + MINI_SIZE;
	max_y = MINI_OFFSET_Y + MINI_SIZE;
	px = rect[0];
	while (px < rect[0] + rect[2])
	{
		py = rect[1];
		while (py < rect[1] + rect[2])
		{
			if (px >= MINI_OFFSET_X && px < max_x && py >= MINI_OFFSET_Y
				&& py < max_y)
				ft_put_pixel(&game->screen, px, py, color);
			py++;
		}
		px++;
	}
}

char	ft_get_cell(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (' ');
	return (game->map[y][x]);
}

int	ft_cell_color(t_game *game, int x, int y, char cell)
{
	if (cell == '1')
		return (MINI_WALL_COLOR);
	if (cell == 'D' && y >= 0 && y < game->map_height && x >= 0
		&& x < game->map_width && game->door_open[y][x] < DOOR_MAX_OPEN)
		return (MINI_DOOR_COLOR);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W'
		|| (cell == 'D' && y >= 0 && y < game->map_height && x >= 0
			&& x < game->map_width && game->door_open[y][x] >= DOOR_MAX_OPEN))
		return (MINI_FLOOR_COLOR);
	return (MINI_VOID_COLOR);
}

void	ft_draw_player(t_game *game, int cx, int cy)
{
	int	dx;
	int	dy;
	int	i;

	dy = -MINI_PLAYER_RADIUS;
	while (dy <= MINI_PLAYER_RADIUS)
	{
		dx = -MINI_PLAYER_RADIUS;
		while (dx <= MINI_PLAYER_RADIUS)
		{
			if (dx * dx + dy * dy <= MINI_PLAYER_RADIUS * MINI_PLAYER_RADIUS)
				ft_put_pixel(&game->screen, cx + dx, cy + dy,
					MINI_PLAYER_COLOR);
			dx++;
		}
		dy++;
	}
	i = 1;
	while (i <= MINI_TILE_SIZE)
	{
		ft_put_pixel(&game->screen, cx + (int)(game->player.dir_x * i), cy
			+ (int)(game->player.dir_y * i), 0xFFFFFF);
		i++;
	}
}

void	ft_draw_border(t_game *game)
{
	int	i;

	i = 0;
	while (i < MINI_SIZE)
	{
		ft_put_pixel(&game->screen, MINI_OFFSET_X + i, MINI_OFFSET_Y,
			MINI_BORDER_COLOR);
		ft_put_pixel(&game->screen, MINI_OFFSET_X + i, MINI_OFFSET_Y + MINI_SIZE
			- 1, MINI_BORDER_COLOR);
		ft_put_pixel(&game->screen, MINI_OFFSET_X, MINI_OFFSET_Y + i,
			MINI_BORDER_COLOR);
		ft_put_pixel(&game->screen, MINI_OFFSET_X + MINI_SIZE - 1, MINI_OFFSET_Y
			+ i, MINI_BORDER_COLOR);
		i++;
	}
}
