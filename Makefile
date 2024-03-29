#---COMMON_VAR-----------------------------------
NAME		=	cub3D
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra -g3
RM			=	rm -rf
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NC			=	\033[0m

#---LIBFT_VAR-------------------------------------
LIBFT_PATH	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
#---MLX_VAR--------------------------------------
MLX_PATH	=	./minilibx/
MLX_SRC		=	libmlx.a
MLX			=	$(addprefix $(MLX_PATH), $(MLX_SRC))
MLX_FLAGS	=	-lX11 -lXext
MLX_EX		=	$(MLX) $(MLX_FLAGS)
#---MINISHELL_VAR----------------------------------
SRC			=	src/main.c \
				src/draw.c \
				src/raycast.c \
				src/mlx_hook.c \
				src/parsing/get_file.c \
				src/parsing/data_init.c \
				src/parsing/parse_data/parse_data.c \
				src/parsing/parse_data/parse_textures.c \
				src/parsing/parse_data/parse_colors.c \
				src/parsing/checker/check_close.c \
				src/parsing/checker/check_data.c \
				src/parsing/checker/check_map.c \
				src/parsing/checker/map_cpy.c \
				src/parsing/checker/expensions.c \
				src/mlx_init.c \
				src/mlx_utils.c \
				src/font.c

OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER_DIR	=	headers/
HEADER_FILE	=	headers/cub3d.h
#---RULES----------------------------------------

all:			lib mlx	$(NAME)

$(NAME):		$(OBJS) $(HEADER)
				@echo "\033[0;33m\nCOMPILING cub3d...\n"
				@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX_EX) -o $@ -lm
				@echo "\033[1;32m./cub3d created\n"

lib:
				@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
				@make -C $(LIBFT_PATH)
				@echo "\033[1;32mLIBFT_lib created\n"

mlx:
				@echo "\033[0;33m\nCOMPILING $(MLX_PATH)...\n"
				@make -C $(MLX_PATH)
				@echo "\033[1;32mMLX_lib created\n"

$(OBJS_DIR)%.o:	%.c | dir
				$(CC) $(FLAGS) -c $< -o $@

dir:			$(OBJS_DIR)

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)src/
				@mkdir -p $(OBJS_DIR)src/parsing/
				@mkdir -p $(OBJS_DIR)src/parsing/parse_data/
				@mkdir -p $(OBJS_DIR)src/parsing/checker/

clean:
				@echo "\033[0;31mDeleting Obj file in $(MLX_PATH)...\n"
				@make clean -sC $(MLX_PATH)
				@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
				@make clean -sC $(LIBFT_PATH)
				@echo "\033[1;32mDone\n"
				@echo "\033[0;31mDeleting cub3d object...\n"
				@$(RM) -rf $(OBJS_DIR)
				@echo "\033[1;32mDone\n"

fclean:			clean
				@echo "\033[0;31mDeleting cub3d executable..."
				@rm -rf $(NAME)
				@make fclean -C $(LIBFT_PATH)
				@echo "\033[1;32mDone\n"

re:				fclean all

.PHONY:			all clean fclean
