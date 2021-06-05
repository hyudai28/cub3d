/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:17:57 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 19:41:44 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
**
**          floor_casting
**
*/

/*
    //rayDir for left most ray (x = 0) and rightmost ray (x = w)
    //current y position compared to the center of the screen (the horizon)
    //int p = y - height / 2;
    //Vertical position of the camera
    //float posZ = 0.5 * height;
    //Horizon distance from the camera to the floor for the current row.
    //0.5 is the z position exactly in the middle between floor and ceiling.
    //float rowDistance = (0.5 * height) / (y - height / 2);//p;
*/

t_floor_struct	input_fl_struct(t_info *info, int y, t_floor_struct floor)
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;

	rayDirX0 = info->dirX - info->planeX;
	rayDirY0 = info->dirY - info->planeY;
	rayDirX1 = info->dirX + info->planeX;
	rayDirY1 = info->dirY + info->planeY;
	floor.floorStepX = (0.5 * info->s_height)
		/ (y - info->s_height / 2) * (rayDirX1 - rayDirX0) / info->s_width;
	floor.floorStepY = (0.5 * info->s_height)
		/ (y - info->s_height / 2) * (rayDirY1 - rayDirY0) / info->s_width;
	floor.floorX = info->posX + (0.5 * info->s_height)
		/ (y - info->s_height / 2) * rayDirX0;
	floor.floorY = info->posY + (0.5 * info->s_height)
		/ (y - info->s_height / 2) * rayDirY0;
	return (floor);
}

//the cell coord is simply got from the integer parts of floorX and floorY.
//get the texture coordinate from the fractional part
t_floor_cell	input_floor_cell(t_floor_struct floor, t_floor_cell ret)
{
	ret.cellX = (int)floor.floorX;
	ret.cellY = (int)floor.floorY;
	ret.tx = (int)(TEXWIDTH * (floor.floorX - ret.cellX)) & (TEXWIDTH - 1);
	ret.ty = (int)(TEXHEIGHT * (floor.floorY - ret.cellY)) & (TEXHEIGHT - 1);
	return (ret);
}

int	checkerBoardPattern(int cellX, float floorX)
{
	int	checkerBoardPattern;

	checkerBoardPattern = (int)(cellX - floorX) & 1;
	if (checkerBoardPattern == 0)
		return (3);
	else
		return (4);
}

//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
void	determine_color(t_info *info, t_floor_cell cell_fl, int x, int y)
{
	(void)cell_fl;
	info->buf[y][x] = info->fl_color;
	info->buf[info->s_height - y - 1][x] = info->clg_color;
}

void	floor_casting(t_info *info, int y)
{
	t_floor_struct	floor;
	t_floor_cell	cell_fl;
	int				x;
	int				floorTexture;

	while (y < info->s_height)
	{
		floor = input_fl_struct(info, y, floor);
		x = 0;
		while (x < info->s_width)
		{
			cell_fl = input_floor_cell(floor, cell_fl);
			floor.floorX += floor.floorStepX;
			floor.floorY += floor.floorStepY;
			floorTexture = checkerBoardPattern(cell_fl.cellX, floor.floorX);
			determine_color(info, cell_fl, x, y);
			x++;
		}
		y++;
	}
}
