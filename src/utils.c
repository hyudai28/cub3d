/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:18:31 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 21:10:17 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_rgb(int R, int G, int B)
{
	int	r;
	int	g;
	int	b;

	r = (int)R;
	g = (int)G;
	b = (int)B;
	r = r << 16;
	g = g << 8;
	b = b << 0;
	return (r + g + b);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data
			[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], info->dir_texture[0], &img);
	load_image(info, info->texture[1], info->dir_texture[1], &img);
	load_image(info, info->texture[2], info->dir_texture[2], &img);
	load_image(info, info->texture[3], info->dir_texture[3], &img);
}

int	push_exit(t_info *info)
{
	(void)info;
	system("leaks cub3D");
	printf("you click esc, bye!\n");
	exit(0);
}
