# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:    :+:            #
#                                                     +:+ +:+         +:+      #
#    By: makurek <makurek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 22:14:00 by makurek           #+#    #+#              #
#    Updated: 2026/01/12 11:13:21 by makurek        ########   odam.nl         #
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
EXEC_DIR	:= exec
VEC3_DIR	:= vec3
PARSE_DIR	:= parse

UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_DIR		:= minilibx-linux
	MLX_INC		:= -I$(MLX_DIR)
	MLX_LINK	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
	MLX_DIR		:= minilibx-macos
	MLX_INC		:= -I$(MLX_DIR)
	MLX_LINK	:= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error Unsupported OS: $(UNAME_S))
endif

SRC_FILES	:= main.c input.c libx.c
EXEC_FILES	:= put_image.c rays.c colors.c sphere.c objects.c interval.c utils.c plane.c cylinder.c light.c
VEC3_FILES	:= vec3_construct.c vec3_inplace.c vec3_ops.c vec3_ops2.c vec3_length.c vec3_random.c
PARSE_FILES	:= parser.c parse_line.c parse_colors.c parse_numbers.c parse_vectors.c scene_to_world.c parse_elements.c parse_objects.c
EXEC_PREFIX	:= $(SRC_DIR)/$(EXEC_DIR)/
VEC3_PREFIX	:= $(EXEC_PREFIX)$(VEC3_DIR)/
PARSE_PREFIX:= $(SRC_DIR)/$(PARSE_DIR)/
SRC			:= $(addprefix $(SRC_DIR)/,$(SRC_FILES)) $(addprefix $(EXEC_PREFIX),$(EXEC_FILES)) \
			   $(addprefix $(VEC3_PREFIX),$(VEC3_FILES)) $(addprefix $(PARSE_PREFIX),$(PARSE_FILES)) 
OBJ			:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
INC			:= -I$(INC_DIR) $(MLX_INC) -I$(LIBFT_DIR)/$(INC_DIR)
MLX			:= $(MLX_LINK)

LIBFT		:= $(LIBFT_DIR)/libft.a

DIRS		:= $(INC_DIR) $(SRC_DIR) $(OBJ_DIR) $(LIBFT_DIR) $(SRC_DIR)/$(EXEC_DIR) $(EXEC_PREFIX)$(VEC3_DIR) $(OBJ_DIR)/$(EXEC_DIR) \
			   $(OBJ_DIR)/$(EXEC_DIR)/$(VEC3_DIR) $(SRC_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(PARSE_DIR)

all: $(NAME) 
	echo "Done!"
	#explain usage?

CMLX:
	echo "Compiling MLX..."
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
