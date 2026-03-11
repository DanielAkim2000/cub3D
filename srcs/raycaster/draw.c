/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:03:50 by demane            #+#    #+#             */
/*   Updated: 2026/03/10 18:47:17 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

// fonction pour calculer la distance perpendiculaire
void	ft_calculate_perp_dist(t_game *game)
{
	// Porte : panel centré dans la tile (demi-pas) pour éviter l'effet cube
	if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
	{
		if (game->ray.side == 0)
			game->ray.perp_wall_dist = (game->ray.map_x + 0.5
					- game->player.pos_x) / game->ray.ray_dir_x;
		else
			game->ray.perp_wall_dist = (game->ray.map_y + 0.5
					- game->player.pos_y) / game->ray.ray_dir_y;
		return ;
	}
	// mur vertical (touché en X)
	if (game->ray.side == 0)
	{
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos_x + (1
					- game->ray.step_x) / 2) / game->ray.ray_dir_x;
	}
	// mur horizontal (touché en Y)
	else
	{
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos_y + (1
					- game->ray.step_y) / 2) / game->ray.ray_dir_y;
	}
}

// fonction pour calculer la hauteur du mur
void	ft_calculate_wall_height(t_game *game)
{
	// cqlcule la hauteur
	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	if (game->ray.line_height == 0)
		game->ray.line_height = 1;
	// calcule start et end draw
	game->ray.draw_start = -(game->ray.line_height / 2) + HEIGHT / 2;
	game->ray.draw_end = (game->ray.line_height / 2) + HEIGHT / 2;
	// securite pour rster dans l ecran
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}

// fonction pour dessiner une colonne
void	ft_draw_column(t_game *game, int x)
{
	double	wall_x;
	int		tex_x;
	int		tex_num;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;
	int		color;

	// calccul des coordonnes de texture
	wall_x = ft_get_wall_x(game);
	tex_num = ft_get_wall_texture_num(game);
	tex_x = ft_get_tex_x(game, wall_x, tex_num);
	step = (double)game->textures[tex_num].height / game->ray.line_height;
	tex_pos = (game->ray.draw_start - HEIGHT / 2 + game->ray.line_height / 2)
		* step;
	// dessiner le plafond de 0 a draw_start
	y = 0;
	while (y < game->ray.draw_start)
	{
		ft_put_pixel(&game->screen, x, y, game->ceil_color);
		y++;
	}
	// dessine le mur de draw_start a draw_end
	y = game->ray.draw_start;
	while (y <= game->ray.draw_end)
	{
		tex_y = (int)tex_pos % game->textures[tex_num].height;
		tex_pos += step;
		color = ft_get_texture_pixel(game, tex_num, tex_x, tex_y);
		ft_put_pixel(&game->screen, x, y, color);
		y++;
	}
	// dessiner le sol de draw end a height
	y = game->ray.draw_end + 1;
	while (y < HEIGHT)
	{
		ft_put_pixel(&game->screen, x, y, game->floor_color);
		y++;
	}
}
