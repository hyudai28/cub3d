/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_cub2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:16:33 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/04 22:17:51 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_xpm(char *xpm_line, int xpm_fd)
{
	int		gnl_ret;
	char	*gnl_line;

	check_xpm_line(xpm_line);
	gnl_ret = get_next_line(xpm_fd, &gnl_line);
	while (gnl_ret)
	{
		if (gnl_line[0] == '"')
		{
			if (gnl_line[1] == '6' && gnl_line[2] == '4'
				&& gnl_line[4] == '6' && gnl_line[5] == '4')
			{
				free(gnl_line);
				gnl_line = NULL;
				return (0);
			}
		}
		free(gnl_line);
		gnl_line = NULL;
		gnl_ret = get_next_line(xpm_fd, &gnl_line);
	}
	if (gnl_ret != -1)
		free(gnl_line);
	return (1);
}

int	check_texture(char *line)
{
	int		map_index;
	int		fd;
	char	*dst;
	char	*trim;

	map_index = skip_spaces(line, 2);
	dst = ft_strdup(&line[map_index]);
	trim = ft_strtrim(dst, " ");
	free(dst);
	fd = open(trim, O_RDONLY);
	if (fd != -1)
	{
		if (check_xpm(trim, fd) == 0)
		{
			free(trim);
			trim = NULL;
			close(fd);
			return (0);
		}
	}
	free(trim);
	trim = NULL;
	printf("Only 64 x 64 xpm files can be used.\n");
	return (1);
}

int	ceil_floor_count(t_count *w_h, int num)
{
	if (num == 1)
		w_h->C = 1;
	else
	{
		w_h->F = 1;
	}
	return (0);
}

int	check_color(char *line, int num, t_count *w_h)
{
	int	map_index;
	int	color;
	int	index;
	int	len;

	len = ft_strlen(line);
	map_index = skip_spaces(line, 1);
	index = 0;
	while (index < 3)
	{
		color = ft_atoi(&line[map_index]);
		while (ft_isdigit(line[map_index]) && line[map_index])
			map_index++;
		map_index = skip_spaces(line, map_index);
		if (line[map_index] == ',')
			map_index++;
		if (!(0 <= color && color <= 255))
			return (1);
		map_index = skip_spaces(line, map_index);
		index++;
	}
	if (line[map_index] != '\0')
		return (1);
	return (ceil_floor_count(w_h, num));
}

int	check_map(t_info *info, t_count *w_h, char *line)
{
	int		map_index;

	map_index = 0;
	while ((ft_isdigit(line[map_index]) || line[map_index] == 'N'
			|| line[map_index] == 'S' || line[map_index] == 'W'
			|| line[map_index] == 'E') && line[map_index])
	{
		if (line[map_index] == 'N' || line[map_index] == 'S'
			|| line[map_index] == 'W' || line[map_index] == 'E')
		{
			if (w_h->PLAYER == 1)
				map_error();
			w_h->PLAYER = 1;
			info->sprite_count++;
		}
		map_index++;
		map_index = skip_spaces(line, map_index);
	}
	if (line[map_index] != '\0')
		return (1);
	if (map_index > w_h->mapwidth)
		w_h->mapwidth = map_index;
	if (map_index != 0)
		w_h->mapheight++;
	return (0);
}
