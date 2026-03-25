/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_free_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:15:26 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:22:13 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_free_int_tab(int **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_double_tab(double **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_map_free(t_map_check *m)
{
	int	i;

	if (!m || !m->map)
		return ;
	i = 0;
	while (m->map[i])
	{
		free(m->map[i]);
		i++;
	}
	free(m->map);
	m->map = NULL;
}

void	ft_free_doors(t_game *g, int j)
{
	while (--j >= 0)
	{
		free(g->door_target[j]);
		free(g->door_open[j]);
	}
	free(g->door_target);
	free(g->door_open);
	g->door_target = NULL;
	g->door_open = NULL;
}

void	ft_free_game(t_game *g)
{
	int	i;

	if (!g)
		return ;
	ft_free_int_tab(g->door_target);
	ft_free_double_tab(g->door_open);
	g->door_target = NULL;
	g->door_open = NULL;
	if (g->map)
	{
		i = 0;
		while (g->map[i])
			free(g->map[i++]);
		free(g->map);
		g->map = NULL;
	}
	i = -1;
	while (++i < 5)
	{
		free(g->tex_paths[i]);
		g->tex_paths[i] = NULL;
	}
}
