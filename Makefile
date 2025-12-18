# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 22:14:00 by makurek           #+#    #+#              #
#    Updated: 2025/12/18 17:50:32 by anpayot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT

CC			:= cc 
RM			:= rm -rf
CFLAGS		:= -Wall -Wextra -Werror -g 
MAKE		:= make -s -C

# Detect OS to configure MiniLibX (Linux vs macOS)
UNAME_S	:= $(shell uname -s)

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

# MiniLibX configuration per OS
ifeq ($(UNAME_S),Darwin)
MLX_DIR		:= minilibx-macos
INC_MLX		:= -I$(MLX_DIR)
MLX			:= -L$(MLX_DIR) -lmlx -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore
else
MLX_DIR		:= minilibx-linux
INC_MLX		:= -I$(MLX_DIR)
MLX			:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

INC			:= -I$(INC_DIR) $(INC_MLX) -I$(LIBFT_DIR)/$(INC_DIR)

LIBFT		:= $(LIBFT_DIR)/libft.a

DIRS		:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(LIBFT_DIR) $(SRC_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(PARSE_DIR)

all: $(NAME) 
	echo "Done!"
	#explain usage?

CMLX:
	echo "Compiling MLX in $(MLX_DIR)..."
	$(MAKE) $(MLX_DIR)
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
