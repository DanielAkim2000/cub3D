/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	ft_is_walkable(char c)
{
	return (c == '0' || c == 'D');
}

static int	ft_is_leak(t_game *game, int x, int y)
{
	if (y == 0 || y == game->map_height - 1)
		return (1);
	if (x == 0 || x == (int)ft_strlen(game->map[y]) - 1)
		return (1);
	if (x >= (int)ft_strlen(game->map[y - 1]) || game->map[y - 1][x] == ' ')
		return (1);
	if (x >= (int)ft_strlen(game->map[y + 1]) || game->map[y + 1][x] == ' ')
		return (1);
	if (game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	ft_check_map_closed(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map[y]))
		{
			if (ft_is_walkable(game->map[y][x]) && ft_is_leak(game, x, y))
				return (0);
		}
	}
	return (1);
}
