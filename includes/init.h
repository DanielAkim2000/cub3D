/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:17:22 by demane            #+#    #+#             */
/*   Updated: 2026/03/05 23:27:15 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "base.h"
# include "textures.h"

int		ft_init_game(t_game *game);
int		ft_init_mlx(t_game *game);
void	ft_put_pixel(t_texture *screen, int x, int y, int color);

#endif
