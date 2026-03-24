/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:48:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/23 15:59:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/textures.h"

int	ft_get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = game->textures[tex_num].addr + (tex_y
			* game->textures[tex_num].line_len + tex_x
			* (game->textures[tex_num].bpp / 8));
	return (*(int *)pixel);
}
