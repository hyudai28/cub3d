/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:01:10 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 21:43:50 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	input_allocation(char *line, t_info *info, t_count *w_h, int *spr_index)
{
	int		map_index;
	int		texture_value;

	map_index = skip_spaces(line, 0);
	texture_value = return_texture_value(line);
	if (texture_value)
		return (input_texture(line, info, texture_value));
	else if (line[map_index] == 'F')
		return (input_color(line, info, 0));
	else if (line[map_index] == 'C')
		return (input_color(line, info, 1));
	else if ('0' <= line[map_index] && line[map_index] <= '9')
		return (set_map(line, info, w_h, spr_index));
	return (1);
}

void	put_map(t_info *info, int map_fd, t_count *w_h, int *sprite_index)
{
	char	*gnl_str;
	int		gnl_ret;
	int		map_index;

	gnl_ret = 1;
	map_index = 0;
	while (gnl_ret)
	{
		gnl_ret = get_next_line(map_fd, &gnl_str);
		input_allocation(gnl_str, info, w_h, sprite_index);
		if (gnl_str)
			free(gnl_str);
		gnl_str = NULL;
		map_index++;
	}
	info->map[w_h->input_map_height] = NULL;
	info->spritex[*sprite_index] = -1;
	info->spritey[*sprite_index] = -1;
}

void	input_map(t_info *info, t_count *w_h, char *map)
{
	int		sprite_index;
	int		map_fd;

	sprite_index = 0;
	map_fd = open(map, O_RDONLY);
	if (map_fd == -1)
		map_error();
	map_consistency(info, w_h, map_fd);
	close(map_fd);
	w_h->mapheight++;
	w_h->mapwidth++;
	if (w_h->mapheight < 3 || w_h->mapwidth == 1)
	{
		printf("map is bad\n");
		map_error();
	}
	map_fd = open(map, O_RDONLY);
	setup_map(info, w_h);
	put_map(info, map_fd, w_h, &sprite_index);
	close(map_fd);
	printf("flood fill\n");
	if (flood_fill(w_h, info->map, info->posX, info->posY))
		free_flood(info, w_h);
}
