/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:46:18 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static int	ft_is_blocking(t_game *game, int cy, int cx)
{
	char	cell;

	cell = game->map[cy][cx];
	if (cell == '1')
		return (1);
	if (cell == 'D' && game->door_open[cy][cx] < DOOR_BLOCK_THRESHOLD)
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
