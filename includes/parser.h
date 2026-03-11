/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:39:25 by demane            #+#    #+#             */
/*   Updated: 2026/03/04 14:34:58 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "base.h"
# include <fcntl.h>
/* Parse le fichier .cub et remplit la structure game
 * Retourne 1 si succès, 0 si erreur
 */
int	ft_parse_file(t_game *game, char *filename);

/* Valide l'extension .cub du fichier
 * Retourne 1 si valide, 0 sinon
 */
int	ft_check_extension(char *filename);

/* Parse les éléments de configuration (textures + couleurs)
 * Retourne 1 si succès, 0 si erreur
 */
int	ft_parse_elements(t_game *game, int fd);

/* Parse la map et vérifie qu'elle est fermée
 * Retourne 1 si succès, 0 si erreur
 */
int	ft_parse_map(t_game *game, int fd);

/* Vérifie que la map est entourée de murs (flood fill)
 * Retourne 1 si fermée, 0 sinon
 */
int	ft_check_map_closed(t_game *game);

#endif
