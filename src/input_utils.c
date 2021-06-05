/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:17:14 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 22:09:38 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_spaces(char *str, int index)
{
	while (str[index] && str[index] == ' ')
		index++;
	return (index);
}

void	map_error(void)
{
	printf("map_error\n");
	exit(1);
}

void	print_map(t_info info)
{
	int		i;

	printf("posX=>%f\n", info.posX);
	printf("posY=>%f\n", info.posY);
	printf("NO=>%s\n", info.dir_texture[0]);
	printf("SO=>%s\n", info.dir_texture[1]);
	printf("WE=>%s\n", info.dir_texture[2]);
	printf("EA=>%s\n", info.dir_texture[3]);
	printf("S=>%s\n", info.dir_texture[4]);
	printf("height=>%d\n", info.s_height);
	printf("width=>%d\n", info.s_width);
	i = 0;
	while (info.map[i])
	{
		printf("map[%d]:%s\n", i, info.map[i]);
		i++;
	}
	printf("print fin\n");
}

void	free_flood(t_info *info, t_count *w_h)
{
	int		free_index;

	free_index = 0;
	while (free_index < w_h->mapheight)
	{
		free(info->buf[free_index]);
		free_index++;
	}
	free(info->buf);
	free(info->zBuffer);
	free_index = 0;
	while (free_index < w_h->mapheight)
	{
		free(info->map[free_index]);
		free_index++;
	}
	free(info->map);
	free(info->spritex);
	free(info->spritey);
	exit(1);
}

int	flood_fill(t_count *w_h, char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= w_h->mapwidth - 1
		|| x >= w_h->mapheight - 1)
		map_error();
	else if (map[x][y] == ' ' || map[x][y] == '\0')
		map_error();
	else if (map[x][y] == '1' || map[x][y] == 'X')
		return (0);
	else if (map[x][y] == '0' || map[x][y] == 'N'
			|| map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
	{
		printf("fill\n");
		map[x][y] = 'X';
	}
	flood_fill(w_h, map, x + 1, y);
	flood_fill(w_h, map, x, y + 1);
	flood_fill(w_h, map, x - 1, y);
	flood_fill(w_h, map, x, y - 1);
	return (0);
}
