/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:25:54 by demane            #+#    #+#             */
/*   Updated: 2026/03/10 18:59:32 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

// fonction pour initialiser les valeurs dans le dda
void	ft_init_dda(t_game *game)
{
	// calculer la distance pour traverser une case
	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	// calcule step et side_dist en X
	if (game->ray.ray_dir_x < 0)
	{
		// rayon vers la gauche
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		// rayon vers la droite
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	// calculer stp et side_dist en y
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

// Determine l orientation de la porte selon ses voisins murs
// walls left/right → panel bloque Y (side==1)
// walls up/down → panel bloque X (side==0)
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

// Verifie si le rayon traverse le panel de la porte au milieu du tile
// Si la porte est ouverte,
// le panel ne couvre que 20% du tile (glissee sur le cote)
static int	ft_check_door_hit(t_game *game, int door_dir)
{
	double	door_dist;
	double	door_pos;
	int		mx;
	int		my;
	double	lo;

	mx = game->ray.map_x;
	my = game->ray.map_y;
	if (door_dir == 0)
	{
		door_dist = (mx + 0.5 - game->player.pos_x) / game->ray.ray_dir_x;
		door_pos = game->player.pos_y + door_dist * game->ray.ray_dir_y;
		lo = my;
		if (game->doors[my][mx] == 1)
			lo = my + 0.8;
		return (door_pos >= lo && door_pos < my + 1.0);
	}
	door_dist = (my + 0.5 - game->player.pos_y) / game->ray.ray_dir_y;
	door_pos = game->player.pos_x + door_dist * game->ray.ray_dir_x;
	lo = mx;
	if (game->doors[my][mx] == 1)
		lo = mx + 0.8;
	return (door_pos >= lo && door_pos < mx + 1.0);
}

// fonction pour exec le dda
void	ft_perform_dda(t_game *game)
{
	char	cell;
	int		door_dir;

	while (game->ray.hit == 0)
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
