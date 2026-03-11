# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 11:09:10 by demane            #+#    #+#              #
#    Updated: 2026/03/09 17:03:06 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = @cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux
LDFLAGS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz
MLX = minilibx-linux/libmlx_Linux.a

DIR_SRCS    = srcs
DIR_OBJS    = objs
DIR_INCLUDES= includes

DIR_INIT = init
DIR_PARSER = parser
DIR_HOOKS = hooks
DIR_TEXTURES = textures
DIR_SPRITES = sprites
DIR_RAYCASTER = raycaster
DIR_MINIMAP = minimap

## FILES

FILES_INIT = init_mlx.c init.c
FILES_HOOKS = keys.c mouse.c render.c move.c
FILES_PARSER = parser.c
FILES_RAYCASTER = dda.c draw.c raycast.c
FILES_SPRITES = sprites.c
FILES_TEXTURES = colors.c textures.c
FILES_MINIMAP = minimap.c

## SRCS

SRCS_INIT     = $(addprefix $(DIR_SRCS)/$(DIR_INIT)/, $(FILES_INIT))
SRCS_PARSER   = $(addprefix $(DIR_SRCS)/$(DIR_PARSER)/, $(FILES_PARSER))
SRCS_RAYCASTER = $(addprefix $(DIR_SRCS)/$(DIR_RAYCASTER)/, $(FILES_RAYCASTER))
SRCS_SPRITES = $(addprefix $(DIR_SRCS)/$(DIR_SPRITES)/, $(FILES_SPRITES))
SRCS_TEXTURES = $(addprefix $(DIR_SRCS)/$(DIR_TEXTURES)/, $(FILES_TEXTURES))
SRCS_HOOKS      = $(addprefix $(DIR_SRCS)/$(DIR_HOOKS)/, $(FILES_HOOKS))
SRCS_MINIMAP      = $(addprefix $(DIR_SRCS)/$(DIR_MINIMAP)/, $(FILES_MINIMAP))
MAIN = $(addprefix $(DIR_SRCS)/, main.c)

SRCS = $(SRCS_INIT) $(SRCS_PARSER) $(SRCS_RAYCASTER) $(SRCS_SPRITES) $(SRCS_TEXTURES) $(SRCS_HOOKS) $(SRCS_MINIMAP) $(MAIN)
## OBJS
OBJS = $(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
## LIBFT
DIR_LIBFT = libft
LIBFT = $(DIR_LIBFT)/libft.a
## STYLE
RESET   = \033[0m
GREEN   = \033[32m
CYAN    = \033[36m
BOLD  = \033[1m

BAR_WIDTH = 30
FILE_WIDTH = 40
TOTAL     = $(words $(SRCS))
COUNT     = 0

define progress_bar
	@$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	@PERCENT=$$(($(COUNT) * 100 / $(TOTAL))); \
	FILLED=$$(($(COUNT) * $(BAR_WIDTH) / $(TOTAL))); \
	EMPTY=$$(($(BAR_WIDTH) - $$FILLED)); \
	FILE="$<"; \
	SHORT_FILE=$$(printf "%-*.*s" $(FILE_WIDTH) $(FILE_WIDTH) "$$FILE"); \
	printf "\r\033[K$(BOLD)$(CYAN)[BUILD] [MINISHELL]$(RESET) %s $(CYAN)[" "$$SHORT_FILE"; \
	printf "%0.s=" $$(seq 1 $$FILLED); \
	printf "%0.s " $$(seq 1 $$EMPTY); \
	printf "] %3d%%$(RESET)" $$PERCENT
endef




## RULES

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)
	@printf "\n$(GREEN)✔ Build MINISHELL terminé$(RESET)\n"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	$(progress_bar)

$(LIBFT):
	@make -C $(DIR_LIBFT)

clean:
	@rm -rf $(DIR_OBJS)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
