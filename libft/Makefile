# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alphom <alphom@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 15:59:41 by mwubneh           #+#    #+#              #
#    Updated: 2022/12/17 18:01:24 by alphom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#---COMMON_VAR-----------------------------------
NAME		=	libft.a
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NC			=	\033[0m
#---LIBFT_VAR-------------------------------------
SRC			=	src/ft_isalpha.c\
				src/ft_isdigit.c\
				src/ft_isalnum.c\
				src/ft_isascii.c\
				src/ft_isspace.c\
				src/ft_isprint.c\
				src/ft_strlen.c\
				src/ft_memset.c\
				src/ft_bzero.c\
				src/ft_memcpy.c\
				src/ft_memmove.c\
				src/ft_strlcpy.c\
				src/ft_strlcat.c\
				src/ft_toupper.c\
				src/ft_tolower.c\
				src/ft_strchr.c\
				src/ft_strrchr.c\
				src/ft_strncmp.c\
				src/ft_memchr.c\
				src/ft_memcmp.c\
				src/ft_strnstr.c\
				src/ft_atoi.c\
				src/ft_calloc.c\
				src/ft_strdup.c\
				src/ft_substr.c\
				src/ft_strjoin.c\
				src/ft_strtrim.c\
				src/ft_split.c\
				src/ft_itoa.c\
				src/ft_strmapi.c\
				src/ft_striteri.c\
				src/ft_putchar_fd.c\
				src/ft_putstr_fd.c\
				src/ft_putendl_fd.c\
				src/ft_putnbr_fd.c \
				src/ft_lstadd_back.c\
				src/ft_lstadd_front.c\
				src/ft_lstclear.c\
				src/ft_lstdelone.c\
				src/ft_lstiter.c\
				src/ft_lstlast.c \
				src/ft_lstmap.c\
				src/ft_lstnew.c\
				src/ft_lstsize.c \
				src/gnl/get_next_line.c \
				src/gnl/get_next_line_utils.c
OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER_DIR	=	headers/
HEADER_FILE	=	headers/libft.h \
				headers/get_next_line.h
#---RULES----------------------------------------

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)%.o:%.c Makefile $(HEADER_FILE) | $(OBJS_DIR)
				@$(CC) -I $(HEADER_DIR) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)/src
				@mkdir -p $(OBJS_DIR)/src/gnl
clean:
				@$(RM) $(OBJS_DIR)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
