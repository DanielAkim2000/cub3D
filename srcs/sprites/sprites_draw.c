/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:03:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 16:25:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

int	ft_get_sprite_pixel(t_texture *sprite, int x, int y)
{
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
	return (*(int *)pixel);
}

int	ft_is_transparent(int color)
{
	return ((color & 0x00FFFFFF) == 0x00FF00FF
		|| (color & 0x00FFFFFF) == 0x00000000);
}

static t_texture	*ft_get_weapon_sprite(t_game *game)
{
	if (game->weapon_anim_timer > (WEAPON_ANIM_DURATION - WEAPON_FIRE_DURATION))
		return (&game->weapon[1]);
	return (&game->weapon[0]);
}

static void	ft_draw_weapon_scaled(t_game *game, t_texture *sprite, int size[2],
		int off[2])
{
	int	pos[2];
	int	src[2];
	int	color;

	pos[1] = 0;
	while (pos[1] < size[1])
	{
		src[1] = (pos[1] * sprite->height) / size[1];
		pos[0] = 0;
		while (pos[0] < size[0])
		{
			src[0] = (pos[0] * sprite->width) / size[0];
			color = ft_get_sprite_pixel(sprite, src[0], src[1]);
			if (!ft_is_transparent(color))
				ft_put_pixel(&game->screen, off[0] + pos[0], off[1] + pos[1],
					color);
			pos[0]++;
		}
		pos[1]++;
	}
}

void	ft_draw_weapon(t_game *game)
{
	t_texture	*sprite;
	int			size[2];
	int			off[2];

	sprite = ft_get_weapon_sprite(game);
	size[1] = HEIGHT * WEAPON_SCALE / 100;
	size[0] = (size[1] * sprite->width) / sprite->height;
	off[0] = (WIDTH - size[0]) / 2;
	off[1] = HEIGHT - size[1] + (HEIGHT * 2 / 100);
	if (game->weapon_anim_timer > (WEAPON_ANIM_DURATION - WEAPON_FIRE_DURATION))
		off[1] -= HEIGHT * 2 / 100;
	ft_draw_weapon_scaled(game, sprite, size, off);
}
