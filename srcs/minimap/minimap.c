/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:50:29 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 18:54:16 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minimap.h"

static void	ft_draw_tiles(t_game *game, int center[2], int radius)
{
	int	xy[2];
	int	start[2];
	int	rect[3];

	start[0] = (int)game->player.pos_x - radius;
	start[1] = (int)game->player.pos_y - radius;
	xy[1] = start[1];
	while (xy[1] <= (int)game->player.pos_y + radius)
	{
		xy[0] = start[0];
		while (xy[0] <= (int)game->player.pos_x + radius)
		{
			rect[0] = center[0] + (int)((xy[0] - game->player.pos_x)
					* MINI_TILE_SIZE);
			rect[1] = center[1] + (int)((xy[1] - game->player.pos_y)
					* MINI_TILE_SIZE);
			rect[2] = MINI_TILE_SIZE;
			ft_draw_rect_clipped(game, rect, ft_cell_color(game, xy[0], xy[1],
					ft_get_cell(game, xy[0], xy[1])));
			xy[0]++;
		}
		xy[1]++;
	}
}

void	ft_draw_minimap(t_game *game)
{
	int	center[2];
	int	rect[3];
	int	radius;

	rect[0] = MINI_OFFSET_X;
	rect[1] = MINI_OFFSET_Y;
	rect[2] = MINI_SIZE;
	ft_draw_rect_clipped(game, rect, MINI_VOID_COLOR);
	center[0] = MINI_OFFSET_X + MINI_SIZE / 2;
	center[1] = MINI_OFFSET_Y + MINI_SIZE / 2;
	radius = MINI_SIZE / (2 * MINI_TILE_SIZE) + 2;
	ft_draw_tiles(game, center, radius);
	ft_draw_player(game, center[0], center[1]);
	ft_draw_border(game);
}
