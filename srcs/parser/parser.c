/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:32:02 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	ft_init_parse_fields(t_game *game)
{
	game->tex_paths[4] = NULL;
	game->door_target = NULL;
	game->door_open = NULL;
}

int	ft_check_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	ft_parse_file(t_game *game, char *filename)
{
	int	fd;

	ft_init_parse_fields(game);
	if (!ft_check_extension(filename))
		return (ft_putstr_fd("Error\nInvalid file extension\n", 2), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 0);
	if (!ft_parse_elements(game, fd))
		return (close(fd), 0);
	if (!ft_parse_map(game, fd))
		return (close(fd), 0);
	close(fd);
	if (!ft_check_map_closed(game))
		return (ft_putstr_fd("Error\nMap not closed\n", 2), 0);
	return (1);
}
