# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:33:25 by rbourdon          #+#    #+#              #
#    Updated: 2025/11/21 14:01:06 by rbourdon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf_utils1.c ft_printf_utils2.c ft_printf_utils3.c ft_printf.c ft_hex_worker1.c \
	ft_integers_worker1.c ft_pointers_worker1.c ft_strings_worker1.c ft_uintegers_worker1.c \
	ft_strings_worker2.c ft_hex_worker2.c ft_printf_utils4.c ft_printf_utils5.c

OBJS = $(SRC:.c=.o)
LIBFT = ./libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(LIBFT)
	make $(LIBFT)
	cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $(OBJS)

$(LIBFT):
	@make --directory=./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --directory=./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make --directory=./libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

