/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser_identifiers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:11:52 by rbourdon          #+#    #+#             */
/*   Updated: 2026/03/23 21:22:18 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_int_finder(char *line, int *i, int max, int *out)
{
	int	value;
	int	digit;

	ft_blank_parser(line, i);
	if (!ft_isdigit(line[*i]))
		return (0);
	value = 0;
	while (ft_isdigit(line[*i]))
	{
		digit = line[*i] - '0';
		if (value > (max - digit) / 10)
			return (0);
		value = value * 10 + digit;
		(*i)++;
	}
	*out = value;
	return (1);
}

int	ft_get_identifier_type(const char *id)
{
	if (!ft_strcmp(id, "NO"))
		return (ID_NO);
	if (!ft_strcmp(id, "SO"))
		return (ID_SO);
	if (!ft_strcmp(id, "WE"))
		return (ID_WE);
	if (!ft_strcmp(id, "EA"))
		return (ID_EA);
	if (!ft_strcmp(id, "D"))
		return (ID_D);
	if (!ft_strcmp(id, "F"))
		return (ID_F);
	if (!ft_strcmp(id, "C"))
		return (ID_C);
	return (-1);
}

int	ft_parse_id_helper(t_map_check *m, char *id, char *value, int *type)
{
	*type = ft_get_identifier_type(id);
	if (*type < 0)
		return (ft_error_only("Unknown identifier"), ft_special_free(&id,
				&value, NULL), 0);
	if (m->seen[*type])
		return (ft_error_only("Duplicate identifier"), ft_special_free(&id,
				&value, NULL), 0);
	if (m->id_count == ID_COUNT -1 && *type != ID_D)
		return (ft_error_only("Too many identifiers"), ft_special_free(&id,
				&value, NULL), 0);
	if (*type == ID_F)
	{
		if (!ft_parse_rgb(value, &m->g->floor_color))
			return (ft_error_only("Invalid floor color"), ft_special_free(&id,
					&value, NULL), 0);
	}
	else if (*type == ID_C)
	{
		if (!ft_parse_rgb(value, &m->g->ceil_color))
			return (ft_error_only("Invalid ceiling color"), ft_special_free(&id,
					&value, NULL), 0);
	}
	return (1);
}

int	ft_parse_identifier(t_map_check *m, char *line)
{
	char	*id;
	char	*value;
	int		type;

	if (!ft_split_identifier_value(line, &id, &value))
		return (ft_error_only("Malformed identifier line"),
			ft_special_free(&id, &value, NULL), 0);
	if (!ft_parse_id_helper(m, id, value, &type))
		return (0);
	if (type != ID_F && type != ID_C)
	{
		if (!ft_texture_path_checker(value))
			return (ft_special_free(&id, &value, NULL), 0);
		m->g->tex_paths[type] = ft_strdup(value);
		if (!m->g->tex_paths[type])
			return (ft_error_only("Malloc error"), ft_special_free(&id,
					&value, NULL), 0);
	}
	m->seen[type] = 1;
	if (type != ID_D)
		m->id_count++;
	return (free(id), free(value), 1);
}
