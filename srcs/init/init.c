/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:12:06 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 16:25:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

int	ft_init_game(t_game *game)
{
	if (ft_init_mlx(game))
		return (1);
	ft_load_xpm(game);
	if (ft_load_weapon_sprites(game))
		return (1);
	if (ft_load_torch_sprites(game))
		return (1);
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	game->player.move_forward = 0;
	game->player.move_backward = 0;
	game->player.strafe_left = 0;
	game->player.strafe_right = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
	game->weapon_anim_timer = 0;
	game->weapon_anim_tick = 0;
	game->torch_anim_frame_idx = 0;
	game->torch_anim_tick = 0;
	return (0);
}
