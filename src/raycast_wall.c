/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:18:10 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 19:44:18 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//calculate height of line to draw on screen
//calculate lowest and highest pixel to fill in current stripe
//calculate value of wallX
//where exactly the wall was hit
//x coordinate on the texture
//How much to increase the texture coorinate per screen pixel
//starting texture coordinate
t_draw_wall	draw_setup(t_info *info, t_w_hit wh,
		t_wall_struct w, t_draw_wall dw)
{
	dw = (t_draw_wall){0};
	dw.lineHeight = (int)(info->s_height / wh.perpWallDist);
	if (dw.lineHeight < 0 || dw.lineHeight > 50000)
		dw.lineHeight = 961;
	dw.drawStart = -dw.lineHeight / 2 + info->s_height / 2;
	if (dw.drawStart < 0)
		dw.drawStart = 0;
	dw.drawEnd = dw.lineHeight / 2 + info->s_height / 2;
	if (dw.drawEnd >= info->s_height)
		dw.drawEnd = info->s_height - 1;
	if (wh.side == 0)
		dw.wallX = info->posY + wh.perpWallDist * w.rayDirY;
	else
		dw.wallX = info->posX + wh.perpWallDist * w.rayDirX;
	dw.wallX -= floor(dw.wallX);
	dw.texX = (int)(dw.wallX * (double)TEXWIDTH);
	if (wh.side == 0 && w.rayDirX > 0)
		dw.texX = TEXWIDTH - dw.texX - 1;
	if (wh.side == 1 && w.rayDirY < 0)
		dw.texX = TEXWIDTH - dw.texX - 1;
	dw.step = 1.0 * TEXHEIGHT / dw.lineHeight;
	dw.texPos = (dw.drawStart - info->s_height
			/ 2 + dw.lineHeight / 2) * dw.step;
	return (dw);
}

//texturing calculations
// 1 subtracted from it so that texture 0 can be used!
int	decide_texture(t_wall_struct w, t_w_hit wh)
{
	if (wh.side == 0 && w.stepX == -1)
		return (0);
	else if (wh.side == 0)
		return (1);
	else if (w.stepY == -1)
		return (2);
	else
		return (3);
}

// in while ->cast the texture coordinate to integer, 
// and mask with (texHeight - 1) in case of overflow
// decide color ->make color darker for y-side;
// RGB bytes each divided through two with a "shift" and an "and"
//set the zbuffer for the sprite casting
void	calc_wall_height(t_info *info, t_wall_struct w, t_w_hit wh, int x)
{
	t_draw_wall	dw;
	int			y;
	int			texY;
	int			color;

	dw = (t_draw_wall){};
	dw = draw_setup(info, wh, w, dw);
	y = dw.drawStart;
	while (y < dw.drawEnd)
	{
		texY = (int)dw.texPos & (TEXHEIGHT - 1);
		dw.texPos += dw.step;
		color = info->texture[decide_texture(w, wh)]
		[TEXHEIGHT * texY + dw.texX];
		if (wh.side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][x] = color;
		y++;
	}
	info->zBuffer[x] = wh.perpWallDist;
}

void	wall_casting(t_info *info, int x)
{
	t_wall_struct	w;
	t_w_hit			wh;

	while (x < info->s_width)
	{
		w = input_wall_struct(info, w, x);
		wh = hit_test_to_wall(info, wh, &w);
		calc_wall_height(info, w, wh, x);
		x++;
	}
}
