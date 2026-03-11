/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:18:33 by demane            #+#    #+#             */
/*   Updated: 2026/03/10 13:50:49 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	ft_focus_out(t_game *game)
{
	game->player.move_forward = 0;
	game->player.move_backward = 0;
	game->player.strafe_left = 0;
	game->player.strafe_right = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	if (!ft_parse_file(&game, av[1]))
	{
		ft_putstr_fd("Error\nFailed to parse map file\n", 2);
		return (1);
	}
	if (ft_init_game(&game))
	{
		ft_putstr_fd("Error\nInit game failed\n", 2);
		return (1);
	}
	mlx_hook(game.win, 17, 0, (int (*)())ft_close_window, &game);
	mlx_loop_hook(game.mlx, ft_render_frame, &game);
	mlx_hook(game.win, 2, 1, ft_key_press, &game);
	mlx_hook(game.win, 3, 2, ft_key_release, &game);
	mlx_hook(game.win, 10, 2097152, ft_focus_out, &game);
	game.mouse_enabled = 1;
	mlx_mouse_hide(game.mlx, game.win);
	mlx_mouse_move(game.mlx, game.win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(game.mlx);
	return (0);
}
