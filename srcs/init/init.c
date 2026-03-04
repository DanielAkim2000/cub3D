/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:12:06 by demane            #+#    #+#             */
/*   Updated: 2026/03/04 11:04:26 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

/**
 * position de test, sera remplacé par le parsing
 * regarde vers la gauche au départ
 * plan caméra perpendiculaire → FOV ~66°
 */
static void	ft_init_player(t_game *game)
{
	game->player.pos_x = 2.0;
	game->player.pos_y = 2.0;
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
}

int	ft_init_game(t_game *game)
{
	if (ft_init_mlx(game))
		return (1);
	ft_init_player(game);
	return (0);
}
