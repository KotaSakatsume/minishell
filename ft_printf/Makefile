# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 22:36:28 by kosakats          #+#    #+#              #
#    Updated: 2024/11/20 09:02:13 by kosakats         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
SRCS		=	$(wildcard libft/*.c) srcs/ft_printf.c srcs/ft_putptr_fd.c srcs/ft_putnbr_u_fd.c srcs/ft_puthex_fd.c
INCLUDES	= 	-I./includes
OBJS		=    $(SRCS:.c=.o)
CC			=    cc
CFLAGS		=    -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

$(OBJS): %.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(BONUSOBJS) $(BONUS_FLAG)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus