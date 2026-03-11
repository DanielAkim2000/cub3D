/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:40:01 by demane            #+#    #+#             */
/*   Updated: 2026/03/05 23:01:12 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "base.h"
# include <math.h>

# ifndef WITDH_XPM
#  define WIDTH_XPM 300
# endif

# ifndef HEIGHT_XPM
#  define HEIGHT_XPM 300
# endif

void	ft_load_xpm(t_game *game);
double	ft_get_wall_x(t_game *game);
int		ft_get_tex_x(t_game *game, double wall_x, int tex_num);
int		ft_get_wall_texture_num(t_game *game);

// Accès aux pixels
int		ft_get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y);

#endif
