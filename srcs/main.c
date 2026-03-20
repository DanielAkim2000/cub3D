/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:18:33 by demane            #+#    #+#             */
/*   Updated: 2026/03/20 16:26:36 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2), 1);
	if (!ft_parse_file(&game, av[1]))
		return (ft_putstr_fd("Error\nFailed to parse map file\n", 2), 1);
	if (ft_init_game(&game))
		return (ft_putstr_fd("Error\nInit game failed\n", 2), 1);
	game.mouse_enabled = 1;
	mlx_hook(game.win, 17, 0, (int (*)())ft_close_window, &game);
	mlx_loop_hook(game.mlx, ft_render_frame, &game);
	mlx_hook(game.win, 2, 1, ft_key_press, &game);
	mlx_hook(game.win, 3, 2, ft_key_release, &game);
	return (mlx_mouse_hide(game.mlx, game.win), mlx_mouse_move(game.mlx,
			game.win, WIDTH / 2, HEIGHT / 2), mlx_loop(game.mlx), 0);
}
