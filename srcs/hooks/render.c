/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:25:50 by demane            #+#    #+#             */
/*   Updated: 2026/03/09 17:01:27 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

int	ft_render_frame(t_game *game)
{
	ft_handle_movement(game);
	ft_handle_mouse(game);
	ft_raycast(game);
	ft_draw_minimap(game);
	return (0);
}
