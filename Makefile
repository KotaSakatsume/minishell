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
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./SRCS
BUILT_IN_DIR = ./SRCS/built_in
OBJ_DIR = ./OBJS

INCLUDES = -I includes
LDFLAGS = -lreadline

SRC_FILES = main.c\
			readline_seq.c\
			mk_shell_env.c\
			print_for_debag.c\
			lexer.c\
			lexer_set_token_vals.c\
			lexer_tokenize.c\
			serch_end_ptr.c\
			marge_same_margeid_token.c\
			paser_utils.c\
			parse.c\
			parse_advance.c\
			utils.c\
			utils_struct.c\
			utils_mk_struct.c\
			utils_initialize_struct.c\
			utils_free_struct.c\
			expander.c\
			expander_utils.c\
			expander_quote_and_backslash.c\
			expander_nospace.c\
			expander_token_to_cmd.c\
			ft_exec.c\
            env_list.c\
            ft_execute.c\
            ft_handle_external.c\
            ft_handle_builtin.c\
            ft_redirects.c\
            ft_heredoc.c

SRCS_BUILT_IN = builtin_echo.c\
                builtin_cd.c\
                builtin_env.c\
                builtin_exit.c\
                builtin_export.c\
                builtin_pwd.c\
                builtin_unset.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
       $(addprefix $(BUILT_IN_DIR)/, $(SRCS_BUILT_IN))

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

