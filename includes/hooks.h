/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:40:24 by demane            #+#    #+#             */
/*   Updated: 2026/03/10 13:28:47 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "base.h"
# include "minimap.h"
# include "raycaster.h"
// Boucle de jeu (appelée à chaque frame)
int		ft_render_frame(t_game *game);

// Gestion des touches
int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_game *game);
void	ft_handle_movement(t_game *game);

// Mouvements
void	ft_move_forward(t_game *game);
void	ft_move_backward(t_game *game);
void	ft_strafe_left(t_game *game);
void	ft_strafe_right(t_game *game);

// Rotation
void	ft_rotate_left(t_game *game);
void	ft_rotate_right(t_game *game);

// Collision
int		ft_check_collision(t_game *game, double new_x, double new_y);

// Mouse
int		ft_mouse_move(int x, int y, t_game *game);
void	ft_handle_mouse(t_game *game);

// Close window
int		ft_close_window(t_game *game);

#endif
