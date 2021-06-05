/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:15:37 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 19:46:56 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw(t_info *info)
{
	int		x;
	int		y;

	y = 0;
	while (y < info->s_height)
	{
		x = 0;
		while (x < info->s_width)
		{
			info->img.data[y * info->s_width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	int		y;
	int		x;

	y = info->s_height / 2 + 1;
	floor_casting(info, y);
	x = 0;
	wall_casting(info, x);
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	setup_map(t_info *info, t_count *w_h)
{
	int		malloc_index;

	malloc_index = 0;
	info->texture = (int **)malloc(sizeof(int *) * 5);
	while (malloc_index < 5)
	{
		info->texture[malloc_index] = (int *)malloc(sizeof(int)
				* (TEXHEIGHT * TEXWIDTH));
		malloc_index++;
	}
	malloc_index = 0;
	printf("malloc buf[%d][%d]\n", info->s_height, info->s_width);
	info->buf = malloc(sizeof(int *) * (info->s_height));
	while (malloc_index < info->s_height)
	{
		info->buf[malloc_index] = malloc(sizeof(int) * (info->s_width));
		malloc_index++;
	}
	malloc_index = 0;
	info->zBuffer = malloc(sizeof(double) * (info->s_width));
	info->spriteOrder = malloc(sizeof(int) * (info->sprite_count));
	info->spriteDistance = malloc(sizeof(double) * (info->sprite_count));
	info->map = malloc(sizeof(char *) * (w_h->mapheight));
	info->spritex = malloc(sizeof(int) * (info->sprite_count));
	info->spritey = malloc(sizeof(int) * (info->sprite_count));
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_count	w_h;

	if (argc != 2)
	{
		printf("Please specify only one cub file.\n");
		exit(1);
	}
	info = (t_info){.s_height = 480, .s_width = 640};
	w_h = (t_count){0};
	info.mlx = mlx_init();
	input_map(&info, &w_h, argv[1]);
	print_map(info);
	load_texture(&info);
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	info.win = mlx_new_window(info.mlx, info.s_width, info.s_height, "mlx");
	info.img.img = mlx_new_image(info.mlx, info.s_width, info.s_height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
			&info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, 2, 0, &key_press, &info);
	mlx_hook(info.win, 3, 0, &key_release, &info);
	mlx_hook(info.win, 17, 1L << 17, &push_exit, &info);
	mlx_loop(info.mlx);
}
