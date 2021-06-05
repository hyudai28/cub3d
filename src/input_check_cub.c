/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_cub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:16:17 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 22:17:54 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	return_texture_value(char *line)
{
	int		map_index;

	map_index = skip_spaces(line, 0);
	if (line[map_index] == 'N' && line[map_index + 1] == 'O')
		return (NORTH_TEXTURE);
	else if (line[map_index] == 'S' && line[map_index + 1] == 'O')
		return (SOUTH_TEXTURE);
	else if (line[map_index] == 'W' && line[map_index + 1] == 'E')
		return (WEST_TEXTURE);
	else if (line[map_index] == 'E' && line[map_index + 1] == 'A')
		return (EAST_TEXTURE);
	return (0);
}

int	check_texture_allocation(char *line, t_count *w_h, int texture_value)
{
	int		ret;

	ret = 0;
	if (texture_value == NORTH_TEXTURE && !w_h->N)
		w_h->N = 1;
	else if (texture_value == NORTH_TEXTURE)
		return (1);
	else if (texture_value == SOUTH_TEXTURE && !w_h->SO)
		w_h->SO = 1;
	else if (texture_value == SOUTH_TEXTURE)
		return (1);
	else if (texture_value == WEST_TEXTURE && !w_h->W)
		w_h->W = 1;
	else if (texture_value == WEST_TEXTURE)
		return (1);
	else if (texture_value == EAST_TEXTURE && !w_h->E)
		w_h->E = 1;
	else if (texture_value == EAST_TEXTURE)
		return (1);
	else if (texture_value == SPRITE_TEXTURE)
		return (1);
	ret = check_texture(line);
	return (ret);
}

int	process_allocation(t_info *info, t_count *w_h, char *line)
{
	int		map_index;
	int		texture_value;

	texture_value = return_texture_value(line);
	map_index = skip_spaces(line, 0);
	if (texture_value)
		return (check_texture_allocation(line, w_h, texture_value));
	else if (line[map_index] == 'F' && !w_h->F)
		return (check_color(line, 0, w_h));
	else if (line[map_index] == 'C' && !w_h->C)
		return (check_color(line, 1, w_h));
	else if ((ft_isdigit(line[map_index]) && w_h->MAP != 2)
		|| line[map_index] == ' ')
	{
		w_h->MAP = 1;
		return (check_map(info, w_h, line));
	}
	else if (line[map_index] == '\0')
	{
		if (w_h->MAP == 1)
			w_h->MAP = 2;
		return (0);
	}
	return (1);
}

int	map_consistency(t_info *info, t_count *w_h, int map_fd)
{
	char	*gnl_str;
	int		gnl_ret;

	gnl_ret = 1;
	while (gnl_ret)
	{
		gnl_ret = get_next_line(map_fd, &gnl_str);
		if (process_allocation(info, w_h, gnl_str))
		{
			free(gnl_str);
			gnl_str = NULL;
			map_error();
		}
		free(gnl_str);
		gnl_str = NULL;
	}
	if (!w_h->N || !w_h->SO || !w_h->W || !w_h->E || !w_h->F || !w_h->C
		|| !w_h->MAP || !w_h->PLAYER)
	{
		printf("N%d SO%d W%d E%d F%d C%d MAP%d PLAYER%d\n", w_h->N, w_h->SO, w_h->W, w_h->E, w_h->F ,w_h->C, w_h->MAP, w_h->PLAYER);
		printf("The specified file has more or fewer elements.\n");
		exit(1);
	}
	return (0);
}
