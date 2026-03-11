/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:02:53 by demane            #+#    #+#             */
/*   Updated: 2026/03/11 13:40:21 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

int	ft_key_press(int keycode, t_game *game)
{
	int	door_x;
	int	door_y;

	if (keycode == 65307)
		ft_close_window(game);
	if (keycode == 119)
		game->player.move_forward = 1;
	if (keycode == 115)
		game->player.move_backward = 1;
	if (keycode == 97)
		game->player.strafe_left = 1;
	if (keycode == 100)
		game->player.strafe_right = 1;
	if (keycode == 65361)
		game->player.rotate_left = 1;
	if (keycode == 65363)
		game->player.rotate_right = 1;
	if (keycode == 101)
	{
		door_x = (int)(game->player.pos_x + game->player.dir_x * 1.5);
		door_y = (int)(game->player.pos_y + game->player.dir_y * 1.5);
		if (game->map[door_y][door_x] == 'D')
		{
			if (game->doors[door_y][door_x] == 1)
				game->doors[door_y][door_x] = 0;
			else
				game->doors[door_y][door_x] = 1;
		}
	}
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.move_forward = 0;
	if (keycode == 115)
		game->player.move_backward = 0;
	if (keycode == 97)
		game->player.strafe_left = 0;
	if (keycode == 100)
		game->player.strafe_right = 0;
	if (keycode == 65361)
		game->player.rotate_left = 0;
	if (keycode == 65363)
		game->player.rotate_right = 0;
	return (0);
}

int	ft_close_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->screen.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
