/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:16:58 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 19:41:04 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	input_texture(char *line, t_info *info, int direction)
{
	int		map_index;
	char	*dst;

	direction--;
	map_index = skip_spaces(line, 2);
	dst = ft_strdup(&line[map_index]);
	info->dir_texture[direction] = ft_strtrim(dst, " ");
	free(dst);
	return (0);
}

int	input_color(char *line, t_info *info, int fl_or_clg)
{
	int	map_index;
	int	index;

	map_index = skip_spaces(line, 1);
	index = 0;
	while (index < 3)
	{
		info->fl_clg[fl_or_clg][index] = ft_atoi(&line[map_index]);
		while (ft_isdigit(line[map_index]) && line[map_index])
			map_index++;
		map_index = skip_spaces(line, map_index);
		if (line[map_index] == ',')
			map_index++;
		map_index = skip_spaces(line, map_index);
		index++;
	}
	info->fl_color = create_rgb(info->fl_clg[0][0],
			info->fl_clg[0][1], info->fl_clg[0][2]);
	info->clg_color = create_rgb(info->fl_clg[1][0],
			info->fl_clg[1][1], info->fl_clg[1][2]);
	return (0);
}

void	set_direction(t_info *info, int posX, int posY, char direction)
{
	info->posX = (double)(posY);
	info->posY = (double)(posX);
	if (direction == 'N')
	{
		info->dirX = 1;
		info->planeY = -0.66;
	}
	else if (direction == 'S')
	{
		info->dirX = -1;
		info->planeY = 0.66;
	}
	else if (direction == 'E')
	{
		info->dirY = 1;
		info->planeX = 0.66;
	}
	else if (direction == 'W')
	{
		info->dirY = -1;
		info->planeX = -0.66;
	}
}

int	set_map(char *line, t_info *info, t_count *w_h, int *sprite_index)
{
	int		pos_index;

	info->map[w_h->input_map_height] = ft_strdup(line);
	pos_index = 0;
	while (line[pos_index])
	{
		if (line[pos_index] == 'N' || line[pos_index] == 'S'
			|| line[pos_index] == 'E' || line[pos_index] == 'W')
			set_direction(info, pos_index, w_h->input_map_height,
				line[pos_index]);
		else if (line[pos_index] == '2')
		{
			info->spritex[*sprite_index] = pos_index;
			info->spritey[*sprite_index] = w_h->input_map_height;
			*sprite_index += 1;
		}
		pos_index++;
	}
	w_h->input_map_height++;
	return (0);
}
