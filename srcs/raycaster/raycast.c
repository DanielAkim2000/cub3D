/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:02:55 by demane            #+#    #+#             */
/*   Updated: 2026/03/05 14:36:12 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	ft_init_ray(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x
		* game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y
		* game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	game->ray.hit = 0;
}

void	ft_raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ft_init_ray(game, x);
		ft_init_dda(game);
		ft_perform_dda(game);
		ft_calculate_perp_dist(game);
		ft_calculate_wall_height(game);
		ft_draw_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
