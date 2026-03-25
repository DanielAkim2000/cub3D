/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:20:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 17:19:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

static void	ft_destroy_texture_array(t_game *game, t_texture *array, int count)
{
	int	i;

	if (!game->mlx)
		return ;
	i = 0;
	while (i < count)
	{
		if (array[i].img)
		{
			mlx_destroy_image(game->mlx, array[i].img);
			array[i].img = NULL;
		}
		i++;
	}
}

static void	ft_free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		ft_free((void **)&tab[i++]);
	ft_free((void **)&tab);
}

static void	ft_free_doors_tab(t_game *game)
{
	int	i;

	if (game->door_target)
	{
		i = 0;
		while (game->door_target[i])
			ft_free((void **)&game->door_target[i++]);
		ft_free((void **)&game->door_target);
	}
	if (game->door_open)
	{
		i = 0;
		while (game->door_open[i])
			ft_free((void **)&game->door_open[i++]);
		ft_free((void **)&game->door_open);
	}
}

void	ft_free_game_all(t_game *game)
{
	int	i;

	if (!game)
		return ;
	ft_destroy_texture_array(game, game->textures, MAP_TEXTURE_COUNT);
	ft_destroy_texture_array(game, game->weapon, WEAPON_SPRITE_COUNT);
	ft_destroy_texture_array(game, game->torch, TORCH_SPRITE_COUNT);
	if (game->mlx && game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	game->screen.img = NULL;
	game->win = NULL;
	i = 0;
	while (i < MAP_TEXTURE_COUNT)
		ft_free((void **)&game->tex_paths[i++]);
	ft_free_char_tab(game->map);
	game->map = NULL;
	ft_free_doors_tab(game);
	ft_free((void **)&game->mlx);
}
