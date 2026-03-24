/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:38:58 by demane            #+#    #+#             */
/*   Updated: 2026/03/05 22:34:52 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "base.h"
# include "init.h"
# include "textures.h"
# include <math.h>

/* ========== RAYCAST.C ========== */

/* Fonction principale du raycasting
 * Boucle sur chaque colonne x de l'écran (0 à WIDTH-1)
 * Pour chaque colonne :
 *   1. Calcule la direction du rayon
 *   2. Initialise le DDA
 *   3. Lance le DDA pour trouver le mur
 *   4. Calcule la distance perpendiculaire
 *   5. Calcule la hauteur du mur
 *   6. Dessine la colonne
 */
void	ft_raycast(t_game *game);

/* Initialise les valeurs du rayon pour une colonne x
 * Calcule camera_x, ray_dir_x, ray_dir_y
 * Initialise map_x et map_y (case de départ)
 */
void	ft_init_ray(t_game *game, int x);

/* ========== DDA.C ========== */

/* Initialise les valeurs pour le DDA
 * Calcule :
 *   - delta_dist_x, delta_dist_y (distance pour traverser 1 case)
 *   - step_x, step_y (direction +1 ou -1)
 *   - side_dist_x, side_dist_y (distance jusqu'au 1er croisement)
 */
void	ft_init_dda(t_game *game);

/* Exécute l'algorithme DDA (Digital Differential Analysis)
 * Avance case par case dans la direction du rayon
 * S'arrête quand on touche un mur (map[y][x] == '1')
 * Met à jour :
 *   - ray.map_x, ray.map_y (position du mur touché)
 *   - ray.side (0 = mur vertical, 1 = mur horizontal)
 *   - ray.hit (1 quand un mur est touché)
 */
void	ft_perform_dda(t_game *game);

/* ========== DRAW.C ========== */

/* Calcule la distance perpendiculaire au plan caméra
 * (évite l'effet fish-eye)
 * Formule dépend de ray.side :
 *   - Si side == 0 : distance en X
 *   - Si side == 1 : distance en Y
 */
void	ft_calculate_perp_dist(t_game *game);

/* Calcule la hauteur du mur à afficher et les limites de dessin
 * Met à jour :
 *   - ray.line_height (hauteur en pixels du mur)
 *   - ray.draw_start (pixel de début)
 *   - ray.draw_end (pixel de fin)
 * Clamp les valeurs pour rester dans l'écran
 */
void	ft_calculate_wall_height(t_game *game);

/* Dessine une colonne verticale (x) à l'écran
 * Dessine dans cet ordre :
 *   1. Plafond (de 0 à draw_start) → ceil_color
 *   2. Mur (de draw_start à draw_end) → couleur selon side
 *   3. Sol (de draw_end à HEIGHT) → floor_color
 *
 * Couleurs temporaires (avant textures) :
 *   - Mur vertical (side == 0) : rouge vif 0xFF0000
 *   - Mur horizontal (side == 1) : rouge foncé 0x880000
 */
void	ft_draw_column(t_game *game, int x);

#endif
