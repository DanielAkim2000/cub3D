/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:12:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static void	ft_destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

static void	ft_destroy_weapon(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (game->weapon[i].img)
			mlx_destroy_image(game->mlx, game->weapon[i].img);
		i++;
	}
}

int	ft_close_window(t_game *game)
{
	int	i;

	ft_destroy_textures(game);
	ft_destroy_weapon(game);
	mlx_destroy_image(game->mlx, game->screen.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	i = 0;
	while (i < 5)
		ft_free((void **)&game->tex_paths[i++]);
	ft_free((void **)&game->mlx);
	exit(0);
	return (0);
}
