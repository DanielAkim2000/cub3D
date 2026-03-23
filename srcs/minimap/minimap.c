/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:50:29 by demane            #+#    #+#             */
/*   Updated: 2026/03/21 18:20:30 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

void	ft_draw_tile(t_game *game, int i, int j, int color)
{
	int	px;
	int	py;

	px = 0;
	while (px < MINI_SCALE)
	{
		py = 0;
		while (py < MINI_SCALE)
		{
			ft_put_pixel(&game->screen, i * MINI_SCALE + px, j * MINI_SCALE
				+ py, color);
			py++;
		}
		px++;
	}
}

void	ft_draw_minimap(t_game *game)
{
	int	i;
	int	j;

	j = 1;
	while (j < game->map_height + 1)
	{
		i = 1;
		while (i < game->map_width + 1)
		{
			if (game->map[j - 1][i - 1] == '1')
				ft_draw_tile(game, i, j, MINI_WALL_COLOR);
			else if (game->map[j - 1][i - 1] == 'D' && game->door_open[j - 1][i
				- 1] < DOOR_MAX_OPEN)
				ft_draw_tile(game, i, j, MINI_DOOR_COLOR);
			else if (game->map[j - 1][i - 1] == 'D' && game->door_open[j - 1][i
				- 1] >= DOOR_MAX_OPEN)
				ft_draw_tile(game, i, j, MINI_FLOOR_COLOR);
			else if (game->map[j - 1][i - 1] == '0')
				ft_draw_tile(game, i, j, MINI_FLOOR_COLOR);
			else
				ft_draw_tile(game, i, j, MINI_VOID_COLOR);
			i++;
		}
		j++;
	}
	ft_put_pixel(&game->screen, (int)(game->player.pos_x * MINI_SCALE)
		+ MINI_SCALE, (int)(game->player.pos_y * MINI_SCALE) + MINI_SCALE,
		MINI_PLAYER_COLOR);
}
