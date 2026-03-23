/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:58:42 by demane            #+#    #+#             */
/*   Updated: 2026/03/21 18:14:20 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/textures.h"

static void	ft_load_door_xpm(t_game *game)
{
	if (!game->tex_paths[4])
		return ;
	game->textures[4].img = mlx_xpm_file_to_image(game->mlx, game->tex_paths[4],
			&game->textures[4].width, &game->textures[4].height);
	if (!game->textures[4].img)
	{
		ft_putstr_fd("Error\nTexture not found: ", 2);
		ft_putstr_fd(game->tex_paths[4], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	game->textures[4].addr = mlx_get_data_addr(game->textures[4].img,
			&game->textures[4].bpp, &game->textures[4].line_len,
			&game->textures[4].endian);
}

void	ft_load_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex_paths[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			ft_putstr_fd("Error\nTexture not found: ", 2);
			ft_putstr_fd(game->tex_paths[i], 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
	ft_load_door_xpm(game);
}

double	ft_get_wall_x(t_game *game)
{
	double	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos_y + game->ray.perp_wall_dist
			* game->ray.ray_dir_y;
	else
		wall_x = game->player.pos_x + game->ray.perp_wall_dist
			* game->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	ft_get_tex_x(t_game *game, double wall_x, int tex_num)
{
	double	door_offset;
	int		tex_x;

	if (tex_num == DOOR_TEXTURE_INDEX)
	{
		door_offset = game->door_open[game->ray.map_y][game->ray.map_x];
		if (door_offset > DOOR_MAX_OPEN)
			door_offset = DOOR_MAX_OPEN;
		wall_x -= door_offset;
		if (wall_x < 0.0)
			wall_x = 0.0;
	}
	tex_x = (int)(wall_x * game->textures[tex_num].width);
	if (tex_x >= game->textures[tex_num].width)
		tex_x = game->textures[tex_num].width - 1;
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	return (tex_x);
}

int	ft_get_wall_texture_num(t_game *game)
{
	if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
		return (DOOR_TEXTURE_INDEX);
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			return (3); // EA (Est)
		else
			return (2); // WE (Ouest)
	}
	// Mur horizontal (side == 1) : Nord ou Sud
	else
	{
		if (game->ray.ray_dir_y > 0)
			return (1); // SO (Sud)
		else
			return (0); // NO (Nord)
	}
}

int	ft_get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = game->textures[tex_num].addr + (tex_y
			* game->textures[tex_num].line_len + tex_x
			* (game->textures[tex_num].bpp / 8));
	return (*(int *)pixel);
}
