/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:47:49 by demane            #+#    #+#             */
/*   Updated: 2026/03/10 17:23:26 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "base.h"
# include "init.h"

# define MINI_SCALE 9
# define MINI_WALL_COLOR 0xFFFFFF
# define MINI_FLOOR_COLOR 0x333333
# define MINI_PLAYER_COLOR 0xFF0000
# define MINI_VOID_COLOR 0x000000
# define MINI_DOOR_COLOR 0xD4AA44

void	ft_draw_tile(t_game *game, int i, int j, int color);
void	ft_draw_minimap(t_game *game);

#endif
