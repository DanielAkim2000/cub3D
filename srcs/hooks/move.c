/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:46:18 by demane            #+#    #+#             */
/*   Updated: 2026/03/13 13:59:48 by demane           ###   ########.fr       */
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

static int	ft_is_blocking(t_game *game, int cy, int cx)
{
	char	cell;

	cell = game->map[cy][cx];
	if (cell == '1')
		return (1);
	if (cell == 'D' && game->doors[cy][cx] == 0)
		return (1);
	return (0);
}

int	ft_check_collision(t_game *game, double new_x, double new_y)
{
	if (ft_is_blocking(game, (int)(new_y - MARGIN), (int)(new_x - MARGIN)))
		return (1);
	if (ft_is_blocking(game, (int)(new_y - MARGIN), (int)(new_x + MARGIN)))
		return (1);
	if (ft_is_blocking(game, (int)(new_y + MARGIN), (int)(new_x - MARGIN)))
		return (1);
	if (ft_is_blocking(game, (int)(new_y + MARGIN), (int)(new_x + MARGIN)))
		return (1);
	return (0);
}

void	ft_move_forward(t_game *game)
{
	double		new_x;
	double		new_y;
	double		old_x;
	double		old_y;
	t_player	*p;

	p = &game->player;
	old_x = p->pos_x;
	old_y = p->pos_y;
	new_x = old_x + p->dir_x * p->move_speed;
	new_y = old_y + p->dir_y * p->move_speed;
	if (!ft_check_collision(game, new_x, old_y))
		p->pos_x = new_x;
	if (!ft_check_collision(game, old_x, new_y))
		p->pos_y = new_y;
}

void	ft_move_backward(t_game *game)
{
	double		new_x;
	double		new_y;
	double		old_x;
	double		old_y;
	t_player	*p;

	p = &game->player;
	old_x = p->pos_x;
	old_y = p->pos_y;
	new_x = old_x - p->dir_x * p->move_speed;
	new_y = old_y - p->dir_y * p->move_speed;
	if (!ft_check_collision(game, new_x, old_y))
		p->pos_x = new_x;
	if (!ft_check_collision(game, old_x, new_y))
		p->pos_y = new_y;
}

void	ft_strafe_right(t_game *game)
{
	double		new_x;
	double		new_y;
	double		old_x;
	double		old_y;
	t_player	*p;

	p = &game->player;
	old_x = p->pos_x;
	old_y = p->pos_y;
	new_x = old_x + p->plane_x * p->move_speed;
	new_y = old_y + p->plane_y * p->move_speed;
	if (!ft_check_collision(game, new_x, old_y))
		p->pos_x = new_x;
	if (!ft_check_collision(game, old_x, new_y))
		p->pos_y = new_y;
}

void	ft_strafe_left(t_game *game)
{
	double		new_x;
	double		new_y;
	double		old_x;
	double		old_y;
	t_player	*p;

	p = &game->player;
	old_x = p->pos_x;
	old_y = p->pos_y;
	new_x = old_x - p->plane_x * p->move_speed;
	new_y = old_y - p->plane_y * p->move_speed;
	if (!ft_check_collision(game, new_x, old_y))
		p->pos_x = new_x;
	if (!ft_check_collision(game, old_x, new_y))
		p->pos_y = new_y;
}

void	ft_handle_movement(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->rotate_left)
		ft_rotate_left(game);
	if (p->rotate_right)
		ft_rotate_right(game);
	if (p->move_backward)
		ft_move_backward(game);
	if (p->move_forward)
		ft_move_forward(game);
	if (p->strafe_left)
		ft_strafe_left(game);
	if (p->strafe_right)
		ft_strafe_right(game);
}
