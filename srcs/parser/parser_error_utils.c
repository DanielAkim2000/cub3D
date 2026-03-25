/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:09:13 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/25 16:55:15 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_free_parser_and_error(t_map_check *m, char *s)
{
	int	i;

	get_next_line(-1);
	if (s)
		ft_error_only(s);
	if (!m)
		return ;
	ft_map_free(m);
	if (m->fd > 2)
		close(m->fd);
	i = -1;
	while (++i < MAP_TEXTURE_COUNT)
	{
		if (m->g->tex_paths[i])
		{
			free(m->g->tex_paths[i]);
			m->g->tex_paths[i] = NULL;
		}
	}
}

void	ft_special_free(char **a, char **b, char **c)
{
	if (a)
	{
		free (*a);
		*a = NULL;
	}
	if (b)
	{
		free (*b);
		*b = NULL;
	}
	if (c)
	{
		free (*c);
		*c = NULL;
	}
}

void	ft_error_only(char *s)
{
	ssize_t	ret;

	ret = write(2, "Error\n", 6);
	(void)ret;
	ret = write(2, s, ft_strlen(s));
	(void)ret;
	ret = write(2, "\n", 1);
	(void)ret;
}
