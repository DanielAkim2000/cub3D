/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_items.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:38:08 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/24 22:00:00 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	ft_map_pos_check(t_map_check *m, int i, int j)
{
	if (j < 0 || !m->map[j])
		return (' ');
	if (i < 0 || i >= (int)ft_strlen(m->map[j]))
		return (' ');
	return (m->map[j][i]);
}

int	ft_is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'T');
}

int	ft_door_check(t_map_check *m, int i, int j)
{
	if (ft_is_blank(ft_map_pos_check(m, i, j - 1))
		|| ft_is_blank(ft_map_pos_check(m, i, j + 1))
		|| ft_is_blank(ft_map_pos_check(m, i - 1, j))
		|| ft_is_blank(ft_map_pos_check(m, i + 1, j)))
		return (ft_error_only("Door must not be at the edges of the map"), 0);
	if ((ft_map_pos_check(m, i - 1, j) == '1'
			&& ft_map_pos_check(m, i + 1, j) == '1'
			&& ft_is_walkable(ft_map_pos_check(m, i, j - 1))
			&& ft_is_walkable(ft_map_pos_check(m, i, j + 1)))
		|| (ft_map_pos_check(m, i, j - 1) == '1'
			&& ft_map_pos_check(m, i, j + 1) == '1'
			&& ft_is_walkable(ft_map_pos_check(m, i - 1, j))
			&& ft_is_walkable(ft_map_pos_check(m, i + 1, j))))
		return (1);
	return (ft_error_only("Misplaced door on the map"), 0);
}

int	ft_player_check(t_map_check *m, int i, int j, int *p)
{
	(*p)++;
	if (*p > 1)
		return (ft_error_only("Only one player allowed on the map"), 0);
	if (ft_is_blank(ft_map_pos_check(m, i, j - 1))
		|| ft_is_blank(ft_map_pos_check(m, i, j + 1))
		|| ft_is_blank(ft_map_pos_check(m, i - 1, j))
		|| ft_is_blank(ft_map_pos_check(m, i + 1, j)))
		return (ft_error_only("Map must be surrounded by walls"), 0);
	return (1);
}

int	ft_floor_check(t_map_check *m, int i, int j)
{
	if (ft_is_blank(ft_map_pos_check(m, i, j - 1))
		|| ft_is_blank(ft_map_pos_check(m, i, j + 1))
		|| ft_is_blank(ft_map_pos_check(m, i - 1, j))
		|| ft_is_blank(ft_map_pos_check(m, i + 1, j)))
		return (ft_error_only("Map must be surrounded by walls"), 0);
	return (1);
}
