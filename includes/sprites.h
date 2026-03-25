/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:39:41 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 14:04:29 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "base.h"

int		ft_load_weapon_sprites(t_game *game);
int		ft_load_torch_sprites(t_game *game);
void	ft_update_weapon_animation(t_game *game);
void	ft_update_torch_animation(t_game *game);
void	ft_draw_weapon(t_game *game);
void	ft_draw_torch_sprites(t_game *game);
int		ft_get_sprite_pixel(t_texture *sprite, int x, int y);
int		ft_is_transparent(int color);

#endif
