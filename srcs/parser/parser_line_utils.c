/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:26:35 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:22:42 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_remove_nl(char *line)
{
	char	*nl;

	if (!line)
		return ;
	nl = ft_strchr(line, '\n');
	if (nl)
		*nl = '\0';
}

int	ft_append_map_line(t_map_check *m, char *line)
{
	int		i;
	char	**new_map;
	char	*copy;

	ft_remove_nl(line);
	copy = ft_strdup(line);
	if (!copy)
		return (0);
	i = 0;
	while (m->map && m->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (free(copy), 0);
	i = 0;
	while (m->map && m->map[i])
	{
		new_map[i] = m->map[i];
		i++;
	}
	new_map[i++] = copy;
	new_map[i] = NULL;
	free(m->map);
	m->map = new_map;
	return (1);
}

int	ft_parse_line_out_map(char *trim, t_map_check *m, char *line, int *in_map)
{
	ft_remove_nl(line);
	if (!ft_is_map_line(line))
		return (free(trim), ft_error_only("Invalid line before map"), 0);
	if (m->id_count != ID_COUNT - 1)
		return (free(trim), ft_error_only("Map starts before all identifiers"),
			0);
	*in_map = 1;
	if (!ft_append_map_line(m, line))
		return (free(trim), ft_error_only("Malloc error"), 0);
	return (free(trim), 1);
}

int	ft_parse_line_in_map(char *trim, t_map_check *m, char *line)
{
	if (*trim == '\0')
		return (free(trim), ft_error_only("Empty line inside map"), 0);
	ft_remove_nl(line);
	if (!ft_is_map_line(line))
		return (free(trim), ft_error_only("Invalid content after map started"),
			0);
	if (!ft_append_map_line(m, line))
		return (free(trim), ft_error_only("Malloc error"), 0);
	return (free(trim), 1);
}

int	ft_parse_line(t_map_check *m, char *line, int *in_map)
{
	char	*trim;

	trim = ft_special_strtrim(line, " \t\n");
	if (!trim)
		return (0);
	if (!*in_map)
	{
		if (*trim == '\0')
			return (free(trim), 1);
		if (!ft_is_map_line(line))
		{
			if (!ft_parse_identifier(m, trim))
				return (free(trim), 0);
			return (free(trim), 1);
		}
		return (ft_parse_line_out_map(trim, m, line, in_map));
	}
	return (ft_parse_line_in_map(trim, m, line));
}
