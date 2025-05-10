NAME   = minishell

SRCS   = src/test.c \
			src/execution.c
OBJS = $(SRCS:.c=.o)

CC     = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Ilibft
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS)  $(LIBFT_LIB) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_B)  $(LIBFT_LIB) -o $(NAME_B)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(OBJS_B)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_B)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re