NAME 		= miniRT

CC 			= cc
RM			= rm -f

CFLAGS 		+= -Wall -Wextra -Werror -O3
CLINKS		= -ldl -lglfw -pthread -lm

LIBMLX_DIR	= minilibx
LIBMLX 		= $(LIBMLX_DIR)/libmlx42.a

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LIBKDM_DIR	= kdm
LIBKDM		= $(LIBKDM_DIR)/libkdm.a

SRC 		= cleanup.c\
			  draw.c\
			  hook.c\
			  miniRT.c\
			  mlx_utils.c\
			  object/all.c\
			  object/hit_cylinder.c\
			  object/hit_plane.c\
			  object/hit_sky.c\
			  object/hit_sphere.c\
			  object/hit_triangle.c\
			  object/ray_cylinder.c\
			  object/ray_plane.c\
			  object/ray_sphere.c\
			  object/ray_triangle.c\
			  parse_elements.c\
			  parse_objects.c\
			  parse_texture.c\
			  parse_utils.c\
			  parsing.c\
			  phong.c\
			  pixel_color.c\
			  utils.c

OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(LIBKDM) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBMLX) $(LIBFT) $(LIBKDM) $(CLINKS)

$(LIBMLX): $(LIBMLX_DIR)
	cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)	
	$(MAKE) -C $(LIBMLX_DIR)

$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBKDM): $(LIBKDM_DIR)
	$(MAKE) -C $(LIBKDM_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBMLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBKDM_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBMLX)
	$(RM) $(LIBFT)
	$(RM) $(LIBKDM)
	$(RM) $(NAME)

re: fclean all

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all bonus clean fclean re
