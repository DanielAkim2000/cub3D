/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:03:50 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	ft_calculate_perp_dist(t_game *game)
{
	if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
	{
		if (game->ray.side == 0)
			game->ray.perp_wall_dist = (game->ray.map_x + 0.5
					- game->player.pos_x) / game->ray.ray_dir_x;
		else
			game->ray.perp_wall_dist = (game->ray.map_y + 0.5
					- game->player.pos_y) / game->ray.ray_dir_y;
		return ;
	}
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos_x + (1
					- game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos_y + (1
					- game->ray.step_y) / 2) / game->ray.ray_dir_y;
}

void	ft_calculate_wall_height(t_game *game)
{
	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	if (game->ray.line_height == 0)
		game->ray.line_height = 1;
	game->ray.draw_start = -(game->ray.line_height / 2) + HEIGHT / 2;
	game->ray.draw_end = (game->ray.line_height / 2) + HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}

void	ft_draw_column(t_game *game, int x)
{
	double	wall_x;
	double	tex[2];
	int		v[4];

	wall_x = ft_get_wall_x(game);
	v[0] = ft_get_wall_texture_num(game);
	v[1] = ft_get_tex_x(game, wall_x, v[0]);
	tex[0] = (double)game->textures[v[0]].height / game->ray.line_height;
	tex[1] = (game->ray.draw_start - HEIGHT / 2 + game->ray.line_height / 2)
		* tex[0];
	v[2] = -1;
	while (++v[2] < HEIGHT)
	{
		if (v[2] < game->ray.draw_start)
			ft_put_pixel(&game->screen, x, v[2], game->ceil_color);
		else if (v[2] <= game->ray.draw_end)
		{
			v[3] = (int)tex[1] % game->textures[v[0]].height;
			tex[1] += tex[0];
			ft_put_pixel(&game->screen, x, v[2], ft_get_texture_pixel(game,
					v[0], v[1], v[3]));
		}
		else
			ft_put_pixel(&game->screen, x, v[2], game->floor_color);
	}
}
