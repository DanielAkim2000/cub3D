/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:12:00 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 17:19:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"
#include "../../includes/init.h"

int	ft_close_window(t_game *game)
{
	ft_free_game_all(game);
	exit(0);
	return (0);
}
