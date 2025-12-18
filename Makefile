# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:    :+:            #
#                                                     +:+ +:+         +:+      #
#    By: makurek <makurek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 22:14:00 by makurek           #+#    #+#              #
#    Updated: 2025/12/18 16:34:43 by makurek        ########   odam.nl         #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT

CC			:= cc 
RM			:= rm -rf
CFLAGS		:= -Wall -Wextra -Werror -g 
MAKE		:= make -s -C

LIBFT_DIR	:= libft
SRC_DIR		:= sources
OBJ_DIR		:= objects
INC_DIR		:= includes
PARSE_DIR	:= parse

SRC_FILES	:= main.c input.c libx.c put_image.c rays.c vec3.c colors.c
PARSE_FILES	:= parser.c
SRC_PREFIX	:= $(SRC_DIR)/
PARS_PREFIX	:= $(SRC_DIR)/$(PARSE_DIR)/
SRC			:= $(addprefix $(SRC_DIR)/,$(SRC_FILES)) $(addprefix $(PARS_PREFIX),$(PARSE_FILES))
OBJ			:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
INC			:= -I$(INC_DIR) -Iminilibx-linux -I$(LIBFT_DIR)/$(INC_DIR)
MLX			:= -Lminilibx-linux -lmlx -lXext -lX11 -lm

LIBFT		:= $(LIBFT_DIR)/libft.a

DIRS		:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(LIBFT_DIR) $(SRC_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(PARSE_DIR)

all: $(NAME) 
	echo "Done!"
	#explain usage?

CMLX:
	echo "Compiling MLX..."
	$(MAKE) minilibx-linux
	echo "MLX compiled successfully."

$(NAME): $(OBJ) $(LIBFT) CMLX
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DIRS):
	mkdir -p $@

$(LIBFT):
	$(MAKE) $(LIBFT_DIR)

clean:	
	$(RM) $(OBJ_DIR)
	$(MAKE) $(LIBFT_DIR) clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) $(LIBFT_DIR) fclean

re:	fclean all 

.SILENT:
.PHONY: all clean fclean test re
