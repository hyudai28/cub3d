/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:15:56 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 19:48:37 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include "./../mlx/mlx.h"
# include "mlx.h"
# include "key_macro.h"
# include "./../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define TEXWIDTH 64
# define TEXHEIGHT 64

//texture define
# define CEILING_TEXTURE 6
# define FLOOR_TEXTURE 3
# define NORTH_TEXTURE 1
# define SOUTH_TEXTURE 2
# define WEST_TEXTURE 3
# define EAST_TEXTURE 4
# define SPRITE_TEXTURE 5

//sprite define
# define UDIV 1
# define UDIV 1
# define VMOVE 0.0

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_count
{
	int		mapwidth;
	int		mapheight;
	int		N;
	int		SO;
	int		W;
	int		E;
	int		F;
	int		C;
	int		MAP;
	int		PLAYER;
	int		input_map_height;
}			t_count;

typedef struct s_info
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	void	*mlx;
	void	*win;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_right;
	int		key_left;
	int		key_esc;
	int		key_print;
	t_img	img;
	int		fl_clg[2][3];
	int		fl_color;
	int		clg_color;
	int		**buf;
	double	*zBuffer;
	int		**texture;
	char	*dir_texture[5];
	double	moveSpeed;
	double	rotSpeed;
	char	**map;
	int		s_width;
	int		s_height;
	int		*spritex;
	int		*spritey;
	int		*spriteOrder;
	double	*spriteDistance;
	int		sprite_count;
}			t_info;

typedef struct s_pair
{
	double		first;
	int			second;
}				t_pair;

//draw floor and ceil
typedef struct s_floor_struct
{
	float		floorStepX;
	float		floorStepY;
	float		floorX;
	float		floorY;
}				t_floor_struct;

typedef struct s_floor_cell
{
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
}				t_floor_cell;

// wall casting
typedef struct s_wall_struct
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			stepX;
	int			stepY;
}				t_wall_struct;

typedef struct s_w_hit
{
	int		hit;
	int		side;
	double	perpWallDist;
}				t_w_hit;

typedef struct s_draw_wall
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
}			t_draw_wall;

//input_map
void			input_map(t_info *info, t_count *w_h,
					char *map);
void			put_map(t_info *info, int map_fd,
					t_count *w_h, int *sprite_index);
int				input_allocation(char *line, t_info *info, t_count *w_h,
					int *sprite_index);

//input_map2.c
int				set_map(char *line, t_info *info,
					t_count *w_h, int *sprite_index);
void			set_direction(t_info *info, int posX,
					int posY, char direction);
int				input_color(char *line, t_info *info, int fl_or_clg);
int				input_texture(char *line, t_info *info, int direction);

//input_check_cub
int				map_consistency(t_info *info, t_count *w_h, int map_fd);
int				process_allocation(t_info *info, t_count *w_h, char *line);
int				check_texture_allocation(char *line,
					t_count *w_h, int texture_value);
int				return_texture_value(char *line);

//input_check_cub2
int				check_map(t_info *info, t_count *w_h, char *line);
int				check_color(char *line, int num, t_count *w_h);
int				ceil_floor_count(t_count *w_h, int num);
int				check_texture(char *line);
int				check_xpm(char *xpm_line, int xpm_fd);

//input_utils
int				flood_fill(t_count *w_h, char **map, int x, int y);
void			free_flood(t_info *info, t_count *w_h);
void			print_map(t_info info);
void			map_error(void);
int				skip_spaces(char *str, int index);

/****************************************************************
**
**          ray_casting
**
****************************************************************/
//raycast_floor.c
void			floor_casting(t_info *info, int y);
void			determine_color(t_info *info,
					t_floor_cell cell_fl, int x, int y);
int				checkerBoardPattern(int cellX, float floorX);
t_floor_cell	input_floor_cell(t_floor_struct floor, t_floor_cell ret);
t_floor_struct	input_fl_struct(t_info *info, int y, t_floor_struct floor);

//raycast_wall.c
void			wall_casting(t_info *info, int x);
void			calc_wall_height(t_info *info,
					t_wall_struct w, t_w_hit wh, int x);
int				decide_texture(t_wall_struct w, t_w_hit wh);
t_draw_wall		draw_setup(t_info *info, t_w_hit wh, t_wall_struct w,
					t_draw_wall dw);

//raycast_wall2.c
t_w_hit			hit_test_to_wall(t_info *info, t_w_hit wh, t_wall_struct *w);
t_wall_struct	input_wall_struct(t_info *info, t_wall_struct w, int x);
void			input_side_step(t_info *info, t_wall_struct *w);

//keypush.c
void			key_update(t_info *info);
void			key_update_ADP(t_info *info);
void			key_update_RLE(t_info *info);
int				key_release(int key, t_info *info);
int				key_press(int key, t_info *info);

//utils.c
int				push_exit(t_info *info);
void			load_texture(t_info *info);
void			load_image(t_info *info, int *texture, char *path, t_img *img);
int				create_rgb(int R, int G, int B);

//main.c
void			setup_map(t_info *info, t_count *w_h);
int				create_rgb(int R, int G, int B);

int				confirm_cub_file(char *line);
void			argc_check(int argc);

#endif
