/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:47:31 by demane            #+#    #+#             */
/*   Updated: 2026/03/25 16:56:18 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# define WIDTH 1280
# define HEIGHT 720
# define MARGIN 0.2
# define DOOR_TEXTURE_INDEX 4
# define WALL_TEXTURE_COUNT 4
# define MAP_TEXTURE_COUNT 5
# define DOOR_SLIDE_SPEED 0.02
# define DOOR_MIN_VISIBLE 0.20
# define DOOR_MAX_OPEN 0.80
# define DOOR_BLOCK_THRESHOLD 0.79
# define WEAPON_SPRITE_COUNT 2
# define WEAPON_ANIM_DURATION 16
# define WEAPON_FIRE_DURATION 8
# define WEAPON_ANIM_SPEED 2
# define WEAPON_SCALE 42
# define TORCH_SPRITE_COUNT 4
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02
# define TORCH_ANIM_SPEED 8
# define TORCH_SCALE 35

# define TITLE "cub3D"

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			move_forward;
	int			move_backward;
	int			strafe_left;
	int			strafe_right;
	int			rotate_left;
	int			rotate_right;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			wall_dir;
}				t_ray;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_texture	screen;
	t_texture	textures[MAP_TEXTURE_COUNT];
	t_texture	weapon[WEAPON_SPRITE_COUNT];
	t_texture	torch[TORCH_SPRITE_COUNT];
	char		*tex_paths[MAP_TEXTURE_COUNT];
	t_player	player;
	t_ray		ray;
	char		**map;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceil_color;
	int			**door_target;
	double		**door_open;
	int			mouse_enabled;
	int			mouse_x_prev;
	int			weapon_anim_timer;
	int			weapon_anim_tick;
	int			torch_anim_frame_idx;
	int			torch_anim_tick;
	double		zbuffer[WIDTH];
}				t_game;

typedef struct s_torch_draw
{
	t_texture	*sprite;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			size[2];
	int			start[2];
	int			end[2];
}				t_torch_draw;

#endif
