NAME = cub3D
CC = gcc
CFLAG = -Wall -Wextra -Werror
SOURCE_DIR = src
SOURCE_FILE += $(SOURCE_DIR)/cub3d.c
SOURCE_FILE += $(SOURCE_DIR)/input_check_cub.c
SOURCE_FILE += $(SOURCE_DIR)/input_check_cub2.c
SOURCE_FILE += $(SOURCE_DIR)/input_map.c
SOURCE_FILE += $(SOURCE_DIR)/input_map2.c
SOURCE_FILE += $(SOURCE_DIR)/input_utils.c
SOURCE_FILE += $(SOURCE_DIR)/key_utils.c
SOURCE_FILE += $(SOURCE_DIR)/raycast_floor.c
SOURCE_FILE += $(SOURCE_DIR)/raycast_wall.c
SOURCE_FILE += $(SOURCE_DIR)/raycast_wall2.c
SOURCE_FILE += $(SOURCE_DIR)/utils.c

OBJECT_FILE = $(SOURCE_FILE:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECT_FILE)
			make -C libft
			$(CC) $(OBJECT_FILE) ./libft/libft.a libmlx.dylib -o $(NAME)

.c.o:
		$(CC) $(CFLAG) -c $< -o $@

clean:
		rm -f $(OBJECT_FILE)
		make clean -C libft

fclean: clean
		rm -rf $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re