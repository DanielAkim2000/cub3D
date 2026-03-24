/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:39:25 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 21:39:41 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "base.h"
# include <fcntl.h>

typedef enum e_id
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_D,
	ID_F,
	ID_C,
	ID_COUNT
}	t_id;

typedef struct s_map_check
{
	int		fd;
	int		map_width;
	int		map_height;
	int		in_map;
	int		id_count;
	int		seen[ID_COUNT];
	char	**map;
	int		has_door;
	t_game	*g;
}			t_map_check;

int		ft_parse_file(t_game *g, char *path);
int		ft_split_identifier_value(const char *line, char **id, char **value);
int		ft_is_blank(char c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_error_only(char *s);
void	ft_special_free(char **a, char **b, char **c);
void	ft_free_parser_and_error(t_map_check *m, char *s);
int		ft_parse_identifier(t_map_check *m, char *line);
void	ft_map_free(t_map_check *m);
int		ft_map_name_checker(char *s);
int		ft_map_height(char **map);
int		ft_map_width(char **map);
int		ft_is_map_char(char c);
int		ft_is_map_line(const char *line);
int		ft_door_check(t_map_check *m, int i, int j);
int		ft_player_check(t_map_check *m, int i, int j, int *p);
int		ft_floor_check(t_map_check *m, int i, int j);
int		ft_final_check(t_map_check *m);
int		ft_parse_line(t_map_check *m, char *line, int *in_map);
int		ft_parse_rgb(const char *value, int *color);
char	*ft_special_strtrim(char const *s1, char const *set);
int		ft_texture_path_checker(char *path);
void	ft_free_game(t_game *g);
int		ft_xpm_size_checker(int fd);
void	ft_free_doors(t_game *g, int j);
int		ft_init_doors(t_game *g);
void	ft_blank_parser(char *line, int *i);
void	ft_skip_blank(const char *s, int *i);
int		ft_int_finder(char *line, int *i, int max, int *out);

#endif
