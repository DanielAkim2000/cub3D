/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_torch_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:05:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 16:25:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"
#include "../../includes/sprites.h"

static void	ft_set_torch_bounds(t_torch_draw *d)
{
	int	floor_y;

	floor_y = HEIGHT / 2 + (int)(HEIGHT / (2.0 * d->transform_y));
	d->end[1] = floor_y;
	d->start[1] = d->end[1] - d->size[1];
	d->start[0] = -d->size[0] / 2 + d->screen_x;
	d->end[0] = d->size[0] / 2 + d->screen_x;
	if (d->start[1] < 0)
		d->start[1] = 0;
	if (d->end[1] >= HEIGHT)
		d->end[1] = HEIGHT - 1;
}

static int	ft_init_torch_draw(t_game *game, t_texture *sprite, int tile[2],
		t_torch_draw *d)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	d->sprite = sprite;
	sprite_x = tile[0] + 0.5 - game->player.pos_x;
	sprite_y = tile[1] + 0.5 - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	d->transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	d->transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (d->transform_y <= 0.001)
		return (0);
	d->screen_x = (int)((WIDTH / 2.0) * (1.0 + d->transform_x
				/ d->transform_y));
	d->size[1] = (int)((HEIGHT / d->transform_y) * TORCH_SCALE / 100.0);
	if (d->size[1] < 1)
		return (0);
	d->size[0] = (int)(d->size[1] * ((double)sprite->width / sprite->height));
	if (d->size[0] < 1)
		d->size[0] = 1;
	ft_set_torch_bounds(d);
	return (1);
}

static void	ft_draw_torch_stripe(t_game *game, t_torch_draw *d, int stripe)
{
	int	y;
	int	src[2];
	int	color;

	src[0] = (stripe - d->start[0]) * d->sprite->width / d->size[0];
	y = d->start[1];
	while (y <= d->end[1])
	{
		src[1] = (y - d->start[1]) * d->sprite->height / d->size[1];
		if (src[1] >= 0 && src[1] < d->sprite->height && src[0] >= 0
			&& src[0] < d->sprite->width)
		{
			color = ft_get_sprite_pixel(d->sprite, src[0], src[1]);
			if (!ft_is_transparent(color))
				ft_put_pixel(&game->screen, stripe, y, color);
		}
		y++;
	}
}

static void	ft_draw_torch_at(t_game *game, t_texture *sprite, int tile[2])
{
	t_torch_draw	d;
	int				stripe;

	if (!ft_init_torch_draw(game, sprite, tile, &d))
		return ;
	stripe = d.start[0];
	while (stripe <= d.end[0])
	{
		if (stripe >= 0 && stripe < WIDTH
			&& d.transform_y < game->zbuffer[stripe])
			ft_draw_torch_stripe(game, &d, stripe);
		stripe++;
	}
}

void	ft_draw_torch_sprites(t_game *game)
{
	t_texture	*sprite;
	int			tile[2];

	sprite = &game->torch[game->torch_anim_frame_idx];
	tile[1] = 0;
	while (tile[1] < game->map_height)
	{
		tile[0] = 0;
		while (tile[0] < (int)ft_strlen(game->map[tile[1]]))
		{
			if (game->map[tile[1]][tile[0]] == 'T')
				ft_draw_torch_at(game, sprite, tile);
			tile[0]++;
		}
		tile[1]++;
	}
}
