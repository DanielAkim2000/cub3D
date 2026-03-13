/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:18 by demane            #+#    #+#             */
/*   Updated: 2026/03/13 13:57:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

int	ft_mouse_move(int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)game;
	return (0);
}

void	ft_handle_mouse(t_game *game)
{
	int			x;
	int			y;
	int			delta_x;
	double		angle;
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;

	if (!game->mouse_enabled)
		return ;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	delta_x = -x + (WIDTH / 2);
	if (delta_x == 0)
		return ;
	angle = delta_x * 0.002;
	p = &game->player;
	old_dir_x = p->dir_x;
	p->dir_x = old_dir_x * cos(-angle) - p->dir_y * sin(-angle);
	p->dir_y = old_dir_x * sin(-angle) + p->dir_y * cos(-angle);
	old_plane_x = p->plane_x;
	p->plane_x = old_plane_x * cos(-angle) - p->plane_y * sin(-angle);
	p->plane_y = old_plane_x * sin(-angle) + p->plane_y * cos(-angle);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
}
