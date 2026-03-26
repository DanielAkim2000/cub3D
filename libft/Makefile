# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:33:25 by rbourdon          #+#    #+#              #
#    Updated: 2026/03/26 18:23:24 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CPPFLAGS    := -I. -Ift_printf -Iget_next_line

SRC_LIBFT = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	  ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_putstr_fd.c ft_split.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strchr.c \
	  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_back.c \
	  ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	  ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_free.c

SRC_PRINTF = ft_printf/ft_printf_utils1.c ft_printf/ft_printf_utils2.c ft_printf/ft_printf_utils3.c ft_printf/ft_printf.c ft_printf/ft_hex_worker1.c \
	ft_printf/ft_integers_worker1.c ft_printf/ft_pointers_worker1.c ft_printf/ft_strings_worker1.c ft_printf/ft_uintegers_worker1.c \
	ft_printf/ft_strings_worker2.c ft_printf/ft_hex_worker2.c ft_printf/ft_printf_utils4.c ft_printf/ft_printf_utils5.c

ifeq ($(GNL_BONUS),1)
OBJDIR := obj_bonus
SRC_GNL := get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
else
OBJDIR := obj
SRC_GNL := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
endif

SRCS = $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL)

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

CC = @cc
CFLAGS = -Wall -Wextra -Werror

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
	printf "\r\033[K$(BOLD)$(CYAN)[BUILD] [LIBFT]$(RESET) %s $(CYAN)[" "$$SHORT_FILE"; \
	printf "%0.s=" $$(seq 1 $$FILLED); \
	printf "%0.s " $$(seq 1 $$EMPTY); \
	printf "] %3d%%$(RESET)" $$PERCENT
endef

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\n$(GREEN)✔ Build LIBFT terminé$(RESET)\n"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@
	$(progress_bar)

clean:
	@rm -rf obj obj_bonus

fclean: clean
	@rm -f $(NAME)

gnl_bonus:
	@$(MAKE) GNL_BONUS=1 $(NAME)

-include $(DEPS)

re: fclean all

.PHONY: all clean fclean re bonus

