/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:47:49 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "base.h"
# include "init.h"

# define MINI_TILE_SIZE 9
# define MINI_SIZE 180
# define MINI_OFFSET_X 20
# define MINI_OFFSET_Y 20
# define MINI_PLAYER_RADIUS 3
# define MINI_WALL_COLOR 0xFFFFFF
# define MINI_FLOOR_COLOR 0x333333
# define MINI_PLAYER_COLOR 0xFF0000
# define MINI_VOID_COLOR 0x000000
# define MINI_DOOR_COLOR 0xD4AA44
# define MINI_BORDER_COLOR 0xAAAAAA

void	ft_draw_minimap(t_game *game);
void	ft_draw_rect_clipped(t_game *game, int rect[3], int color);
char	ft_get_cell(t_game *game, int x, int y);
int		ft_cell_color(t_game *game, int x, int y, char cell);
void	ft_draw_player(t_game *game, int cx, int cy);
void	ft_draw_border(t_game *game);

#endif
