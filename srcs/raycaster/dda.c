/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:25:54 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	ft_init_dda(t_game *game)
{
	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	if (game->ray.ray_dir_x < 0)
		game->ray.step_x = -1;
	else
		game->ray.step_x = 1;
	if (game->ray.ray_dir_x < 0)
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	else
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	if (game->ray.ray_dir_y < 0)
		game->ray.step_y = -1;
	else
		game->ray.step_y = 1;
	if (game->ray.ray_dir_y < 0)
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	else
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
}

static int	ft_get_door_dir(t_game *game, int mx, int my)
{
	int	walls_x;
	int	walls_y;

	walls_x = (game->map[my][mx - 1] == '1') + (game->map[my][mx + 1] == '1');
	walls_y = (game->map[my - 1][mx] == '1') + (game->map[my + 1][mx] == '1');
	if (walls_x > walls_y)
		return (1);
	return (0);
}

static int	ft_check_door_hit(t_game *game, int door_dir)
{
	double	door_dist;
	double	door_pos;
	double	lo;
	double	open_ratio;

	open_ratio = game->door_open[game->ray.map_y][game->ray.map_x];
	if (open_ratio > DOOR_MAX_OPEN)
		open_ratio = DOOR_MAX_OPEN;
	if (door_dir == 0)
	{
		door_dist = (game->ray.map_x + 0.5 - game->player.pos_x)
			/ game->ray.ray_dir_x;
		door_pos = game->player.pos_y + door_dist * game->ray.ray_dir_y;
		lo = game->ray.map_y + open_ratio;
		return (door_pos >= lo && door_pos < game->ray.map_y + 1.0);
	}
	door_dist = (game->ray.map_y + 0.5 - game->player.pos_y)
		/ game->ray.ray_dir_y;
	door_pos = game->player.pos_x + door_dist * game->ray.ray_dir_x;
	lo = game->ray.map_x + open_ratio;
	return (door_pos >= lo && door_pos < game->ray.map_x + 1.0);
}

static void	ft_step_ray(t_game *game)
{
	if (game->ray.side_dist_x < game->ray.side_dist_y)
	{
		game->ray.side_dist_x += game->ray.delta_dist_x;
		game->ray.map_x += game->ray.step_x;
		game->ray.side = 0;
	}
	else
	{
		game->ray.side_dist_y += game->ray.delta_dist_y;
		game->ray.map_y += game->ray.step_y;
		game->ray.side = 1;
	}
}

void	ft_perform_dda(t_game *game)
{
	char	cell;
	int		door_dir;

	while (game->ray.hit == 0)
	{
		ft_step_ray(game);
		cell = game->map[game->ray.map_y][game->ray.map_x];
		if (cell == '1')
			game->ray.hit = 1;
		else if (cell == 'D')
		{
			door_dir = ft_get_door_dir(game, game->ray.map_x, game->ray.map_y);
			if (game->ray.side == door_dir && ft_check_door_hit(game, door_dir))
				game->ray.hit = 1;
		}
	}
}
