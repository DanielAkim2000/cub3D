/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:18 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 16:02:35 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

int	ft_mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && game->shoot_anim_timer == 0)
	{
		game->shoot_anim_timer = WEAPON_ANIM_FRAMES;
		game->shoot_anim_tick = 0;
	}
	return (0);
}

void	ft_handle_mouse(t_game *game)
{
	int		x;
	int		y;
	int		delta_x;
	double	angle;
	double	old[2];

	if (!game->mouse_enabled)
		return ;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	delta_x = -x + (WIDTH / 2);
	if (delta_x == 0)
		return ;
	angle = delta_x * 0.002;
	old[0] = game->player.dir_x;
	game->player.dir_x = old[0] * cos(-angle) - game->player.dir_y
		* sin(-angle);
	game->player.dir_y = old[0] * sin(-angle) + game->player.dir_y
		* cos(-angle);
	old[1] = game->player.plane_x;
	game->player.plane_x = old[1] * cos(-angle) - game->player.plane_y
		* sin(-angle);
	game->player.plane_y = old[1] * sin(-angle) + game->player.plane_y
		* cos(-angle);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
}
