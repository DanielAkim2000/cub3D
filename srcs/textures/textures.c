/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:58:42 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 17:19:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/textures.h"
#include "../../includes/init.h"

static void	ft_load_door_xpm(t_game *game)
{
	if (!game->tex_paths[DOOR_TEXTURE_INDEX])
		return ;
	game->textures[DOOR_TEXTURE_INDEX].img = mlx_xpm_file_to_image(game->mlx,
			game->tex_paths[DOOR_TEXTURE_INDEX],
			&game->textures[DOOR_TEXTURE_INDEX].width,
			&game->textures[DOOR_TEXTURE_INDEX].height);
	if (!game->textures[DOOR_TEXTURE_INDEX].img)
	{
		ft_putstr_fd("Error\nTexture not found: ", 2);
		ft_putstr_fd(game->tex_paths[DOOR_TEXTURE_INDEX], 2);
		ft_putstr_fd("\n", 2);
		ft_free_game_all(game);
		exit(1);
	}
	game->textures[DOOR_TEXTURE_INDEX].addr = mlx_get_data_addr(
			game->textures[DOOR_TEXTURE_INDEX].img,
			&game->textures[DOOR_TEXTURE_INDEX].bpp,
			&game->textures[DOOR_TEXTURE_INDEX].line_len,
			&game->textures[DOOR_TEXTURE_INDEX].endian);
}

void	ft_load_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < WALL_TEXTURE_COUNT)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex_paths[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			ft_putstr_fd("Error\nTexture not found: ", 2);
			ft_putstr_fd(game->tex_paths[i], 2);
			ft_putstr_fd("\n", 2);
			ft_free_game_all(game);
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
			return (3);
		else
			return (2);
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}
