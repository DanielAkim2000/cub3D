/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:00:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/21 18:09:38 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

static int	ft_get_sprite_pixel(t_texture *sprite, int x, int y)
{
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
	return (*(int *)pixel);
}

static int	ft_is_transparent(int color)
{
	return ((color & 0x00FFFFFF) == 0x00FF00FF);
}

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

void	ft_draw_weapon(t_game *game)
{
	t_texture	*sprite;
	int			size_h;
	int			size_w;
	int			off_x;
	int			off_y;
	int			x;
	int			y;
	int			src_x;
	int			src_y;
	int			color;

	if (game->shoot_anim_timer > (WEAPON_ANIM_FRAMES - WEAPON_FIRE_FRAMES))
		sprite = &game->weapon[1];
	else
		sprite = &game->weapon[0];
	size_h = HEIGHT * WEAPON_SCALE / 100;
	size_w = (size_h * sprite->width) / sprite->height;
	off_x = (WIDTH - size_w) / 2;
	off_y = HEIGHT - size_h + (HEIGHT * 6 / 100);
	if (game->shoot_anim_timer > (WEAPON_ANIM_FRAMES - WEAPON_FIRE_FRAMES))
		off_y -= HEIGHT * 2 / 100;
	y = 0;
	while (y < size_h)
	{
		src_y = (y * sprite->height) / size_h;
		x = 0;
		while (x < size_w)
		{
			src_x = (x * sprite->width) / size_w;
			color = ft_get_sprite_pixel(sprite, src_x, src_y);
			if (!ft_is_transparent(color))
				ft_put_pixel(&game->screen, off_x + x, off_y + y, color);
			x++;
		}
		y++;
	}
}
