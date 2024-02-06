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
#---MINISHELL_VAR----------------------------------
SRC			=	src/main.c \
				src/parsing/get_file.c \
				src/parsing/data_init.c \
				src/parsing/parse_data/parse_data.c \
				src/parsing/parse_data/parse_textures.c \
				src/parsing/parse_data/parse_colors.c \
				src/parsing/checker/check_close.c \
				src/parsing/checker/check_data.c \
				src/parsing/checker/check_map.c \
				src/parsing/checker/map_cpy.c \
				src/parsing/checker/expensions.c

OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER_DIR	=	headers/
HEADER_FILE	=	headers/cub3d.h
#---RULES----------------------------------------

$(NAME):		$(OBJS_DIR) $(LIBFT) Makefile $(HEADER_FILE) $(OBJS)
				@$(CC) $(FLAGS) -g -I $(HEADER_DIR) $(OBJS) $(LIBFT) -o $@
				@echo "\33[2K\r$(GREEN)cub3D compiled$(NC)"


$(OBJS_DIR)%.o:%.c Makefile $(HEADER_FILE) | $(OBJS_DIR)
				@$(CC) -I $(HEADER_DIR) $(FLAGS) -c $< -o $@
				@echo -n "\33[2K\r$(YELLOW)Compiled $<"

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)src
				@mkdir -p $(OBJS_DIR)src/parsing
				@mkdir -p $(OBJS_DIR)src/parsing/parse_data
				@mkdir -p $(OBJS_DIR)src/parsing/checker

all:			$(NAME)

norm:
				@norminette $(SRC) $(HEADER_DIR) | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(NC)"}'

$(LIBFT):
				@echo "$(YELLOW)\nCOMPILING $(LIBFT_PATH)\n"
				@make -sC $(LIBFT_PATH)
				@echo "$(GREEN)LIBFT created\n$(NC)"

clean:
				@echo "$(RED)Deleting Obj file in $(LIBFT_PATH)...\n"
				@make clean -sC $(LIBFT_PATH)
				@echo "$(GREEN)Done\n"
				@echo "$(RED)Deleting cub3D object...\n"
				@$(RM) $(OBJS_DIR)
				@echo "$(GREEN)Done\n"

fclean:			clean
				@echo "$(RED)Deleting cub3D executable..."
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_PATH)
				@echo "$(GREEN)Done\n"

re:				fclean all

.PHONY:			all clean fclean re
