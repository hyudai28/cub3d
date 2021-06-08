
#include "../includes/cub3d.h"

int confirm_cub_file(char *line)
{
	size_t	num;

	num = ft_strlen(line);
	if (line[num - 1] == 'b' &&
	 		line[num - 2] == 'u' &&
	 		line[num - 3] == 'c' &&
	 		line[num - 4] == '.')
			return (0);
	printf("Error.\n");
    printf("file is not cub file\n");
	exit(1);
}

void    argc_check(int argc)
{
    if (argc != 2)
	{
		printf("Error.\n");
        printf("Please specify only one cub file.\n");
		exit(1);
	}
}