# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:33:28 by mkuida            #+#    #+#              #
#    Updated: 2024/11/18 19:33:28 by mkuida           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS =
#CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./SRCS
OBJ_DIR = ./OBJS

INCLUDES = -I includes
LDFLAGS = -lreadline

SRC_FILES = readline.c\
			mk_shell_env.c\
			print_for_debag.c\
			lexer_set_token_vals.c\
			lexer_tokenize.c\
			serch_end_ptr.c\
			marge_same_margeid_token.c\
			paser_utils.c\
			parse.c\
			utils.c\
			utils_mk_struct.c\
			expander.c\
			expander_utils.c\
			expander_quote_and_backslash.c\
			expander_nospace.c\
			expander_token_to_cmd.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

# defo
all: $(NAME)

# bild
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

# make obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# make obj file
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all