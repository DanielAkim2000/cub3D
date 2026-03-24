/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:00:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

int	ft_load_weapon_sprites(t_game *game)
{
	const char	*paths[2] = {"./textures/weapon_idle.xpm",
		"./textures/weapon_fire.xpm"};
	int			i;

	i = 0;
	while (i < 2)
	{
		game->weapon[i].img = mlx_xpm_file_to_image(game->mlx, (char *)paths[i],
				&game->weapon[i].width, &game->weapon[i].height);
		if (!game->weapon[i].img)
			return (ft_putstr_fd("Error\nWeapon sprite not found: ", 2),
				ft_putstr_fd((char *)paths[i], 2), ft_putstr_fd("\n", 2), 1);
		game->weapon[i].addr = mlx_get_data_addr(game->weapon[i].img,
				&game->weapon[i].bpp, &game->weapon[i].line_len,
				&game->weapon[i].endian);
		i++;
	}
	return (0);
}

void	ft_update_weapon_animation(t_game *game)
{
	if (game->shoot_anim_timer > 0)
	{
		game->shoot_anim_tick++;
		if (game->shoot_anim_tick >= WEAPON_ANIM_SPEED)
		{
			game->shoot_anim_tick = 0;
			game->shoot_anim_timer--;
		}
	}
}
