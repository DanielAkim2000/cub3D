/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:18:15 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:23:08 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_parse_rgb_number(const char *s, int *i, int *n)
{
	long	nb;

	ft_skip_blank(s, i);
	if (!ft_isdigit(s[*i]))
		return (0);
	nb = 0;
	while (ft_isdigit(s[*i]))
	{
		nb = (nb * 10) + (s[*i] - '0');
		if (nb > 255)
			return (0);
		(*i)++;
	}
	ft_skip_blank(s, i);
	*n = (int)nb;
	return (1);
}

int	ft_parse_rgb(const char *value, int *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (!value || !color)
		return (0);
	i = 0;
	if (!ft_parse_rgb_number(value, &i, &r))
		return (0);
	if (value[i] != ',')
		return (0);
	i++;
	if (!ft_parse_rgb_number(value, &i, &g))
		return (0);
	if (value[i] != ',')
		return (0);
	i++;
	if (!ft_parse_rgb_number(value, &i, &b))
		return (0);
	if (value[i] != '\0')
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

int	ft_parse_file_helper(t_map_check *m, t_game *g, char *path)
{
	char	*line;
	int		in_map;

	if (!g)
		return (ft_error_only("Game struct is NULL"), 0);
	ft_bzero(m, sizeof(t_map_check));
	ft_bzero(g, sizeof(t_game));
	if (!path)
		return (ft_error_only("Map path is NULL"), 0);
	if (!ft_map_name_checker(path))
		return (0);
	m->fd = open(path, O_RDONLY);
	if (m->fd < 0)
		return (ft_error_only("Cannot open map file"), 0);
	m->g = g;
	in_map = 0;
	line = get_next_line(m->fd);
	while (line)
	{
		if (!ft_parse_line(m, line, &in_map))
			return (free(line), ft_free_parser_and_error(m, NULL), 0);
		free(line);
		line = get_next_line(m->fd);
	}
	return (1);
}

int	ft_parse_file_loop(t_map_check *m, int i)
{
	close(m->fd);
	m->fd = open(m->g->tex_paths[i], O_RDONLY);
	if (m->fd < 0)
		return (ft_free_parser_and_error(m,
				"Texture file cannot be opened"), 0);
	if (!ft_xpm_size_checker(m->fd))
		return (ft_free_parser_and_error(m, NULL), 0);
	get_next_line(-1);
	return (1);
}

int	ft_parse_file(t_game *g, char *path)
{
	t_map_check	m;
	int			i;

	if (!ft_parse_file_helper(&m, g, path))
		return (0);
	if (!m.map)
		return (ft_free_parser_and_error(&m, "Map is missing"), 0);
	if (m.id_count != ID_COUNT - 1)
		return (ft_free_parser_and_error(&m,
				"Missing one or more identifiers"), 0);
	if (!ft_final_check(&m))
		return (ft_free_parser_and_error(&m, NULL), 0);
	i = -1;
	while (++i < 5 && m.g->tex_paths[i])
	{
		if (!ft_parse_file_loop(&m, i))
			return (0);
	}
	close(m.fd);
	g->map = m.map;
	g->map_height = ft_map_height(m.map);
	g->map_width = ft_map_width(m.map);
	if (!ft_init_doors(g))
		return (ft_free_game(g), ft_error_only("Malloc error"), 0);
	return (m.map = NULL, 1);
}
