NAME 		= miniRT

CC 			= cc
RM			= rm -f
CLONE 		= git clone --depth=1

CFLAGS 		+= -Wall #-Wextra -Werror -O3
CLINKS		= -ldl -lglfw -pthread -lm

MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= libft
LIBFT		= $(FT)/libft.a

SRC 		= $(wildcard *.c)
OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	cmake $(MLX) -B $(MLX)	
	$(MAKE) -C $(MLX)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)


$(MLX):
	$(CLONE) https://github.com/kodokaii/MLX42.git $(MLX)

$(FT):
	$(CLONE) https://github.com/kodokaii/libft_plus_plus.git $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(MLX)" ]; then $(MAKE) clean -C $(MLX); fi
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBMLX)
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(MLX) 
	$(RM) -r $(FT)

re: fclean all

.PHONY:		all bonus clear clean fclean re
