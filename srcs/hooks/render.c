/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:25:50 by demane            #+#    #+#             */
/*   Updated: 2026/03/24 16:51:12 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static void	ft_update_door_cell(t_game *game, int y, int x)
{
	double	target;

	target = game->door_target[y][x] * DOOR_MAX_OPEN;
	if (game->door_open[y][x] < target)
		game->door_open[y][x] += DOOR_SLIDE_SPEED;
	else if (game->door_open[y][x] > target)
		game->door_open[y][x] -= DOOR_SLIDE_SPEED;
	if (game->door_open[y][x] < 0.0)
		game->door_open[y][x] = 0.0;
	if (game->door_open[y][x] > DOOR_MAX_OPEN)
		game->door_open[y][x] = DOOR_MAX_OPEN;
}

static void	ft_update_doors(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == 'D')
				ft_update_door_cell(game, y, x);
			x++;
		}
		y++;
	}
}

static void	ft_draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	i = -6;
	while (i <= 6)
	{
		ft_put_pixel(&game->screen, cx + i, cy, 0xFFFFFF);
		ft_put_pixel(&game->screen, cx, cy + i, 0xFFFFFF);
		i++;
	}
}

int	ft_render_frame(t_game *game)
{
	ft_handle_movement(game);
	ft_handle_mouse(game);
	ft_update_weapon_animation(game);
	ft_update_torch_animation(game);
	ft_update_doors(game);
	ft_raycast(game);
	ft_draw_torch_sprites(game);
	ft_draw_minimap(game);
	ft_draw_weapon(game);
	ft_draw_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
