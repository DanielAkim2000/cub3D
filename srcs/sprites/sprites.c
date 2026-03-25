/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:00:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 17:19:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

static void	ft_xpm_load_fatal(t_game *game, char *kind, char *path)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(kind, 2);
	ft_putstr_fd(" not found: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	ft_free_game_all(game);
	exit(1);
}

int	ft_load_weapon_sprites(t_game *game)
{
	const char	*paths[WEAPON_SPRITE_COUNT];
	int			i;

	paths[0] = "./textures/weapon_idle.xpm";
	paths[1] = "./textures/weapon_fire.xpm";
	i = 0;
	while (i < WEAPON_SPRITE_COUNT)
	{
		game->weapon[i].img = mlx_xpm_file_to_image(game->mlx, (char *)paths[i],
				&game->weapon[i].width, &game->weapon[i].height);
		if (!game->weapon[i].img)
			ft_xpm_load_fatal(game, "Weapon sprite", (char *)paths[i]);
		game->weapon[i].addr = mlx_get_data_addr(game->weapon[i].img,
				&game->weapon[i].bpp, &game->weapon[i].line_len,
				&game->weapon[i].endian);
		i++;
	}
	return (0);
}

int	ft_load_torch_sprites(t_game *game)
{
	const char	*paths[TORCH_SPRITE_COUNT];
	int			i;

	paths[0] = "./textures/torch_0.xpm";
	paths[1] = "./textures/torch_1.xpm";
	paths[2] = "./textures/torch_2.xpm";
	paths[3] = "./textures/torch_3.xpm";
	i = 0;
	while (i < TORCH_SPRITE_COUNT)
	{
		game->torch[i].img = mlx_xpm_file_to_image(game->mlx, (char *)paths[i],
				&game->torch[i].width, &game->torch[i].height);
		if (!game->torch[i].img)
			ft_xpm_load_fatal(game, "Torch sprite", (char *)paths[i]);
		game->torch[i].addr = mlx_get_data_addr(game->torch[i].img,
				&game->torch[i].bpp, &game->torch[i].line_len,
				&game->torch[i].endian);
		i++;
	}
	return (0);
}

void	ft_update_weapon_animation(t_game *game)
{
	if (game->weapon_anim_timer > 0)
	{
		game->weapon_anim_tick++;
		if (game->weapon_anim_tick >= WEAPON_ANIM_SPEED)
		{
			game->weapon_anim_tick = 0;
			game->weapon_anim_timer--;
		}
	}
}

void	ft_update_torch_animation(t_game *game)
{
	game->torch_anim_tick++;
	if (game->torch_anim_tick >= TORCH_ANIM_SPEED)
	{
		game->torch_anim_tick = 0;
		game->torch_anim_frame_idx++;
		if (game->torch_anim_frame_idx >= TORCH_SPRITE_COUNT)
			game->torch_anim_frame_idx = 0;
	}
}
