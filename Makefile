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
CFLAGS = #-Wall -Wextra -Werror -g
#CFLAGS += -fsanitize=address -g -O1

SRC_DIR = ./SRCS
BUILT_IN_DIR = ./SRCS/built_in
LEXER_DIR = ./SRCS/lexer
PARSER_DIR = ./SRCS/parser
EXPANDER_DIR = ./SRCS/expander
UTILS_DIR = ./SRCS/utils
EXEC_DIR = ./SRCS/exec

OBJ_DIR = ./OBJS

INCLUDES = -I includes
LDFLAGS = -lreadline

SRC_FILES = main.c\
			signal_handle.c\
			mk_shell_env.c\
			ft_itoa.c\
			env_list.c

SRCS_LEXER =	lexer.c\
				lexer_set_token_vals.c\
				lexer_set_token_stat_vals.c\
				lexer_tokenize.c\
				serch_end_ptr.c\
				readline_seq.c

SRCS_PARSER =	paser_utils.c\
				parse.c\
				parse_free_utils.c\
				parse_cmd.c

SRCS_EXPANDER = marge_same_margeid_token.c\
				expander.c\
				extend_daller.c\
				extend_daller_check_and_expand_mode.c\
				expander_utils.c\
				expander_quote_and_backslash.c\
				expander_nospace.c\
				expander_token_to_cmd.c

SRCS_BUILT_IN = builtin_echo.c\
                builtin_cd.c\
                builtin_env.c\
                builtin_exit.c\
                builtin_export.c\
                builtin_pwd.c\
                builtin_unset.c\
				builtin_export_utils.c\
				buitin_utils.c

SRCS_UTILS =	utils_1.c\
				utils_2.c\
				utils_3.c\
				utils_4.c\
				utils_struct.c\
				utils_mk_struct.c\
				utils_initialize_struct.c\
				utils_free_struct.c

SRCS_EXEC =		ft_exec.c\
				ft_execute.c\
				ft_handle_external.c\
				ft_handle_builtin.c\
				ft_redirects.c\
				ft_heredoc.c\
				ft_exec_utils.c\
				ft_find_path_set.c\
				ft_heredoc_utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
       $(addprefix $(BUILT_IN_DIR)/, $(SRCS_BUILT_IN))

OBJS_SRC = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
OBJS_BUILT_IN = $(SRCS_BUILT_IN:%.c=$(OBJ_DIR)/built_in/%.o)
OBJS_LEXER = $(SRCS_LEXER:%.c=$(OBJ_DIR)/lexer/%.o)
OBJS_PARSER = $(SRCS_PARSER:%.c=$(OBJ_DIR)/parser/%.o)
OBJS_EXPANDER = $(SRCS_EXPANDER:%.c=$(OBJ_DIR)/expander/%.o)
OBJS_UTILS = $(SRCS_UTILS:%.c=$(OBJ_DIR)/utils/%.o)
OBJS_EXEC = $(SRCS_EXEC:%.c=$(OBJ_DIR)/exec/%.o)


OBJS = $(OBJS_SRC) $(OBJS_BUILT_IN) $(OBJS_LEXER) $(OBJS_PARSER) $(OBJS_EXPANDER) $(OBJS_UTILS) $(OBJS_EXEC)


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

# Compile objects for lexer sources
$(OBJ_DIR)/lexer/%.o: $(LEXER_DIR)/%.c | $(OBJ_DIR)/lexer
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile objects for parser sources
$(OBJ_DIR)/parser/%.o: $(PARSER_DIR)/%.c | $(OBJ_DIR)/parser
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile objects for expander sources
$(OBJ_DIR)/expander/%.o: $(EXPANDER_DIR)/%.c | $(OBJ_DIR)/expander
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile objects for utils sources
$(OBJ_DIR)/utils/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)/utils
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile objects for exec sources
$(OBJ_DIR)/exec/%.o: $(EXEC_DIR)/%.c | $(OBJ_DIR)/exec
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/built_in:
	mkdir -p $(OBJ_DIR)/built_in

$(OBJ_DIR)/lexer:
	mkdir -p $(OBJ_DIR)/lexer

$(OBJ_DIR)/parser:
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/expander:
	mkdir -p $(OBJ_DIR)/expander

$(OBJ_DIR)/utils:
	mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/exec:
	mkdir -p $(OBJ_DIR)/exec

# Clean up
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
