/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:06:38 by hyudai            #+#    #+#             */
/*   Updated: 2021/06/11 15:06:51 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	confirm_cub_file(char *line)
{
	size_t	num;

	num = ft_strlen(line);
	if (line[num - 1] == 'b' &&\
			line[num - 2] == 'u' &&\
			line[num - 3] == 'c' &&\
			line[num - 4] == '.')
		return (0);
	printf("Error.\n");
	printf("file is not cub file\n");
	exit(1);
}

void	argc_check(int argc)
{
	if (argc != 2)
	{
		printf("Error.\n");
		printf("Please specify only one cub file.\n");
		exit(1);
	}
}

int	ft_strrchr_int(const char *s, int c)
{
	int		len;

	c = (char)c;
	len = ft_strlen(s) + 1;
	while (len-- != 0)
	{
		if (s[len] == c)
			return (len);
	}
	return (-1);
}

int	check_xpm_line(char *line)
{
	int		len_i;

	len_i = ft_strrchr_int(line, '.');
	if (len_i != -1)
	{
		if (line[++len_i] == 'x' &&\
			line[++len_i] == 'p' &&\
			line[++len_i] == 'm')
			return (0);
	}
	printf("Error.\n");
	printf("this tex is not xpm file.\n");
	exit(1);
}
