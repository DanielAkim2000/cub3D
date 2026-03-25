/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_final_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:41:16 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/24 21:58:19 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_set_player_helper(t_game *g, char c)
{
	if (c == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
	}
}

void	ft_set_player(t_game *g, int i, int j, char c)
{
	g->player.pos_x = i + 0.5;
	g->player.pos_y = j + 0.5;
	if (c == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1;
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
	ft_set_player_helper(g, c);
}

int	ft_final_check_loop(t_map_check *m, int i, int j, int *p)
{
	if (!ft_is_map_char(m->map[j][i]))
		return (ft_error_only("Invalid character in map"), 0);
	if (m->map[j][i] == '0' || m->map[j][i] == 'T')
	{
		if (!ft_floor_check(m, i, j))
			return (0);
	}
	else if (m->map[j][i] == 'D')
	{
		if (!ft_door_check(m, i, j))
			return (0);
		m->has_door++;
	}
	else if (m->map[j][i] == 'N' || m->map[j][i] == 'S'
		|| m->map[j][i] == 'E' || m->map[j][i] == 'W')
	{
		ft_set_player(m->g, i, j, m->map[j][i]);
		if (!ft_player_check(m, i, j, p))
			return (0);
		m->map[j][i] = '0';
	}
	return (1);
}

int	ft_final_check(t_map_check *m)
{
	int	i;
	int	j;
	int	p;

	p = 0;
	j = -1;
	while (m->map[++j])
	{
		i = -1;
		while (m->map[j][++i])
		{
			if (!ft_final_check_loop(m, i, j, &p))
				return (0);
		}
	}
	if (p != 1)
		return (ft_error_only("Map must contain exactly one player"), 0);
	if (m->has_door && !m->seen[ID_D])
		return (ft_error_only("Door texture missing"), 0);
	return (1);
}
