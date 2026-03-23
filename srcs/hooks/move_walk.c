/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static void	ft_try_move(t_game *game, double new_x, double new_y)
{
	double	old_x;
	double	old_y;

	old_x = game->player.pos_x;
	old_y = game->player.pos_y;
	if (!ft_check_collision(game, new_x, old_y))
		game->player.pos_x = new_x;
	if (!ft_check_collision(game, old_x, new_y))
		game->player.pos_y = new_y;
}

void	ft_move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
	ft_try_move(game, new_x, new_y);
}

void	ft_move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.dir_y * game->player.move_speed;
	ft_try_move(game, new_x, new_y);
}

void	ft_strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y + game->player.plane_y * game->player.move_speed;
	ft_try_move(game, new_x, new_y);
}

void	ft_strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
	new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
	ft_try_move(game, new_x, new_y);
}
