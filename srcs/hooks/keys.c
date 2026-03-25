/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:02:53 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 13:37:39 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static void	ft_toggle_front_door(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = (int)(game->player.pos_x + game->player.dir_x * 1.5);
	door_y = (int)(game->player.pos_y + game->player.dir_y * 1.5);
	if (door_x >= game->map_width || door_y >= game->map_height || door_x <= 0
		|| door_y <= 0)
		return ((void)0);
	if (game->map[door_y][door_x] == 'D')
	{
		if (game->door_target[door_y][door_x] >= DOOR_MAX_OPEN)
			game->door_target[door_y][door_x] = 0;
		else
			game->door_target[door_y][door_x] = 1;
	}
}

static void	ft_apply_move_key(t_game *game, int keycode, int value)
{
	if (keycode == 119)
		game->player.move_forward = value;
	if (keycode == 115)
		game->player.move_backward = value;
	if (keycode == 97)
		game->player.strafe_left = value;
	if (keycode == 100)
		game->player.strafe_right = value;
	if (keycode == 65361)
		game->player.rotate_left = value;
	if (keycode == 65363)
		game->player.rotate_right = value;
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_close_window(game);
	ft_apply_move_key(game, keycode, 1);
	if (keycode == 101)
		ft_toggle_front_door(game);
	if (keycode == 108)
		game->mouse_enabled = !game->mouse_enabled;
	if (keycode == 65505)
		game->player.move_speed = MOVE_SPEED * 1.5;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	ft_apply_move_key(game, keycode, 0);
	if (keycode == 65505)
		game->player.move_speed = MOVE_SPEED;
	return (0);
}
