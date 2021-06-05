/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:18:19 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 17:47:57 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	input_side_step(t_info *info, t_wall_struct *w)
{
	if (w->rayDirX < 0)
	{
		w->stepX = -1;
		w->sideDistX = (info->posX - w->mapX) * w->deltaDistX;
	}
	else
	{
		w->stepX = 1;
		w->sideDistX = (w->mapX + 1.0 - info->posX) * w->deltaDistX;
	}
	if (w->rayDirY < 0)
	{
		w->stepY = -1;
		w->sideDistY = (info->posY - w->mapY) * w->deltaDistY;
	}
	else
	{
		w->stepY = 1;
		w->sideDistY = (w->mapY + 1.0 - info->posY) * w->deltaDistY;
	}
}

//which box of the map we're in
//length of ray from current position to next x  or y-side
//double sideDistX;
//double sideDistY;
//lenght of ray from one x or y-side to next x or y-side
t_wall_struct	input_wall_struct(t_info *info, t_wall_struct w, int x)
{
	w = (t_wall_struct){0};
	w.cameraX = 2 * x / (double)info->s_width - 1;
	w.rayDirX = info->dirX + info->planeX * w.cameraX;
	w.rayDirY = info->dirY + info->planeY * w.cameraX;
	w.mapX = (int)info->posX;
	w.mapY = (int)info->posY;
	w.deltaDistX = fabs(1 / w.rayDirX);
	w.deltaDistY = fabs(1 / w.rayDirY);
	input_side_step(info, &w);
	return (w);
}

//calculate DDA and hit test
//Check if ray has hit a wall
//calculate distance of perpendicular ray
//(Euclidean distance will gitve fisheye effect!
t_w_hit	hit_test_to_wall(t_info *info, t_w_hit wh, t_wall_struct *w)
{
	wh = (t_w_hit){};
	while (wh.hit == 0)
	{
		if (w->sideDistX < w->sideDistY)
		{
			w->sideDistX += w->deltaDistX;
			w->mapX += w->stepX;
			wh.side = 0;
		}
		else
		{
			w->sideDistY += w->deltaDistY;
			w->mapY += w->stepY;
			wh.side = 1;
		}
		if (info->map[w->mapX][w->mapY] == '1')
			wh.hit = 1;
	}
	if (wh.side == 0)
		wh.perpWallDist = (w->mapX - info->posX
				+ (1 - w->stepX) / 2) / w->rayDirX;
	else
		wh.perpWallDist = (w->mapY - info->posY
				+ (1 - w->stepY) / 2) / w->rayDirY;
	return (wh);
}
