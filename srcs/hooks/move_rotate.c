/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_rotate_left(t_game *game)
{
	double		new_dir[2];
	double		new_plane[2];
	t_player	*p;

	p = &game->player;
	new_dir[0] = p->dir_x * cos(p->rot_speed) + p->dir_y * sin(p->rot_speed);
	new_dir[1] = -p->dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	new_plane[0] = p->plane_x * cos(p->rot_speed) + p->plane_y
		* sin(p->rot_speed);
	new_plane[1] = -p->plane_x * sin(p->rot_speed) + p->plane_y
		* cos(p->rot_speed);
	p->dir_x = new_dir[0];
	p->dir_y = new_dir[1];
	p->plane_x = new_plane[0];
	p->plane_y = new_plane[1];
}

void	ft_rotate_right(t_game *game)
{
	double		new_dir[2];
	double		new_plane[2];
	t_player	*p;

	p = &game->player;
	new_dir[0] = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	new_dir[1] = p->dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	new_plane[0] = p->plane_x * cos(p->rot_speed) - p->plane_y
		* sin(p->rot_speed);
	new_plane[1] = p->plane_x * sin(p->rot_speed) + p->plane_y
		* cos(p->rot_speed);
	p->dir_x = new_dir[0];
	p->dir_y = new_dir[1];
	p->plane_x = new_plane[0];
	p->plane_y = new_plane[1];
}
