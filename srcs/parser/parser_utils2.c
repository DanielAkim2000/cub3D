/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:20:30 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:23:03 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_xpm_size_check_loop(char *line, int *i, int *width, int *height)
{
	if (!ft_int_finder(line, i, 64, width))
		return (free(line), ft_error_only("Wrong xpm format"), 0);
	if (!ft_int_finder(line, i, 64, height))
		return (free(line), ft_error_only("Wrong xpm format"), 0);
	free(line);
	if (*width == 64 && *height == 64)
		return (1);
	return (ft_error_only("Wrong xpm format"), 0);
}

int	ft_xpm_size_checker(int fd)
{
	char	*line;
	int		i;
	int		width;
	int		height;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (ft_error_only("Wrong xpm format"), 0);
		i = 0;
		ft_blank_parser(line, &i);
		if (line[i] == '"')
		{
			i++;
			return (ft_xpm_size_check_loop(line, &i, &width, &height));
		}
		free(line);
	}
}

int	ft_texture_path_checker(char *path)
{
	int		fd;
	int		len;

	if (!path)
		return (ft_error_only("Texture path is missing"), 0);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (ft_error_only("Texture must be a .xpm file"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error_only("Texture file cannot be opened"), 0);
	close(fd);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_init_doors(t_game *g)
{
	int	j;
	int	width;

	g->door_target = ft_calloc(g->map_height + 1, sizeof(int *));
	g->door_open = ft_calloc(g->map_height + 1, sizeof(double *));
	if (!g->door_target || !g->door_open)
		return (0);
	j = 0;
	while (j < g->map_height)
	{
		width = g->map_width;
		g->door_target[j] = ft_calloc(width + 1, sizeof(int));
		g->door_open[j] = ft_calloc(width + 1, sizeof(double));
		if (!g->door_target[j] || !g->door_open[j])
			return (ft_free_doors(g, j + 1), 0);
		j++;
	}
	return (1);
}
