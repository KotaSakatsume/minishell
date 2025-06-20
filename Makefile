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
SRC_DIR = ./SRCS
BUILT_IN_DIR = ./SRCS/built_in
OBJ_DIR = ./OBJS

INCLUDES = -I includes
LDFLAGS = -lreadline

SRCS_MAIN = readline.c \
            mk_shell_env.c \
            print_for_debag.c \
            lexer_set_token_vals.c \
            lexer_tokenize.c \
            serch_end_ptr.c \
            marge_same_margeid_token.c \
            paser_utils.c \
            parse.c \
            utils.c \
            ft_exec.c \
            env_list.c \
            ft_execute.c \
            ft_handle_external.c \
            ft_handle_builtin.c \
            ft_redirects.c \
            ft_heredoc.c

SRCS_BUILT_IN = builtin_echo.c\
                builtin_cd.c\
                builtin_env.c\
                builtin_exit.c\
                builtin_export.c\
                builtin_pwd.c\
                builtin_unset.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_MAIN)) \
       $(addprefix $(BUILT_IN_DIR)/, $(SRCS_BUILT_IN))

OBJS_MAIN = $(SRCS_MAIN:%.c=$(OBJ_DIR)/%.o)
OBJS_BUILT_IN = $(SRCS_BUILT_IN:%.c=$(OBJ_DIR)/built_in/%.o)
OBJS = $(OBJS_MAIN) $(OBJS_BUILT_IN)

.PHONY: all clean fclean re

# Default
all: $(NAME)

# Build
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compile objects for main sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile objects for built_in sources
$(OBJ_DIR)/built_in/%.o: $(BUILT_IN_DIR)/%.c | $(OBJ_DIR)/built_in
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/built_in:
	mkdir -p $(OBJ_DIR)/built_in

# Clean up
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
