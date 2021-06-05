/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:17:39 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 21:09:57 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
**
**          push key
**
*/
int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
	{
		system("leaks cub3D");
		exit(0);
	}
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_RIGHT)
		info->key_right = 1;
	else if (key == K_LEFT)
		info->key_left = 1;
	else if (key == K_P)
		info->key_print = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_RIGHT)
		info->key_right = 0;
	else if (key == K_LEFT)
		info->key_left = 0;
	else if (key == K_P)
		info->key_print = 0;
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (info->map[(int)(info->posX + info->dirX
				* info->moveSpeed)][(int)(info->posY)] == 'X')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY
				+ info->dirY * info->moveSpeed)] == 'X')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (info->key_s)
	{
		if (info->map[(int)(info->posX - info->dirX
				* info->moveSpeed)][(int)(info->posY)] == 'X')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY
					- info->dirY * info->moveSpeed)] == 'X')
			info->posY -= info->dirY * info->moveSpeed;
	}
	key_update_ADP(info);
	key_update_RLE(info);
}

void	key_update_ADP(t_info *info)
{
	if (info->key_d)
	{
		if (info->map[(int)(info->posX + info->dirY
				* info->moveSpeed)][(int)(info->posY)] == 'X')
			info->posX += info->dirY * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY
				- info->dirX * info->moveSpeed)] == 'X')
			info->posY -= info->dirX * info->moveSpeed;
	}
	if (info->key_a)
	{
		if (info->map[(int)(info->posX - info->dirY
				* info->moveSpeed)][(int)(info->posY)] == 'X')
			info->posX -= info->dirY * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY
				+ info->dirX * info->moveSpeed)] == 'X')
			info->posY += info->dirX * info->moveSpeed;
	}
	if (info->key_print)
	{
		printf("\n\n=======key print=======\n");
		printf("posX = %f posY = %f\n", info->posX, info->posY);
		printf("dirX = %f dirY = %f\n", info->dirX, info->dirY);
		printf("=======print fin =======\n\n");
	}
}

void	key_update_RLE(t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	if (info->key_left)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-0.05) - info->dirY * sin(-0.05);
		info->dirY = oldDirX * sin(-0.05) + info->dirY * cos(-0.05);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-0.05) - info->planeY * sin(-0.05);
		info->planeY = oldPlaneX * sin(-0.05) + info->planeY * cos(-0.05);
	}
	if (info->key_right)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(0.05) - info->dirY * sin(0.05);
		info->dirY = oldDirX * sin(0.05) + info->dirY * cos(0.05);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(0.05) - info->planeY * sin(0.05);
		info->planeY = oldPlaneX * sin(0.05) + info->planeY * cos(0.05);
	}
	if (info->key_esc)
		exit(0);
}
