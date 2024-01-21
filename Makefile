NAME 		= miniRT

CC 			= cc
RM			= rm -f
CLONE 		= git clone --depth=1

CFLAGS 		+= -Wall -Wextra -Werror #-Ofast
CLINKS		= -ldl -lglfw -pthread -lm

MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= libft
LIBFT		= $(FT)/libft.a

KDM			= kdm
LIBKDM		= $(KDM)/libkdm.a

SRC 		= cleanup.c\
			  draw.c\
			  hook.c\
			  miniRT.c\
			  mlx_utils.c\
			  object/all.c\
			  object/cylinder.c\
			  object/plane.c\
			  object/sphere.c\
			  parse_elements.c\
			  parse_objects.c\
			  parse_utils.c\
			  parsing.c\
			  phong.c\
			  utils.c

OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(LIBKDM) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBMLX) $(LIBFT) $(LIBKDM) $(CLINKS)

$(LIBMLX): $(MLX)
	$(MAKE) -C $(MLX)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)

$(LIBKDM): $(KDM)
	$(MAKE) -C $(KDM)

$(MLX):
	$(CLONE) https://github.com/kodokaii/MLX42.git $(MLX)
	cmake $(MLX) -B $(MLX)	

$(FT):
	$(CLONE) https://github.com/kodokaii/libft_plus_plus.git $(FT)

$(KDM):
	$(CLONE) https://github.com/kodokaii/kdm.git $(KDM)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(MLX)" ]; then $(MAKE) clean -C $(MLX); fi
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	if [ -d "$(KDM)" ]; then $(MAKE) clean -C $(KDM); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBMLX)
	$(RM) $(LIBFT)
	$(RM) $(LIBKDM)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(MLX) 
	$(RM) -r $(FT)
	$(RM) -r $(KDM)

re: fclean all

.PHONY:		all bonus clear clean fclean re
