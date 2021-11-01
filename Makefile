# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malatini <malatini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 13:57:54 by malatini          #+#    #+#              #
#    Updated: 2021/09/30 20:54:22 by malatini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC	= \033[0m
RED	= \033[0;91m
GREEN =	\033[0;92m

SRC		=	./srcs/main/main.c \
			./srcs/parsing/parse_main.c \
			./srcs/parsing/init.c \
			./srcs/parsing/parse_sub.c \
			./srcs/parsing/parsing_utils.c \
			./srcs/parsing/parsing_utils1.c \
			./srcs/parsing/parsing_utils2.c \
			./srcs/parsing/parse_main_utils.c \
			./srcs/parsing/parse_errors.c \
			./srcs/execution/builtins/cd.c \
			./srcs/execution/builtins/echo.c \
			./srcs/execution/builtins/env.c \
			./srcs/execution/builtins/pwd.c \
			./srcs/execution/builtins/exit.c \
			./srcs/execution/builtins/exit_utils.c \
			./srcs/execution/builtins/unset.c \
			./srcs/execution/builtins/export.c \
			./srcs/execution/builtins/export_utils.c \
			./srcs/execution/builtins/export_utils1.c \
			./srcs/execution/builtins/export_utils2.c \
			./srcs/execution/builtins/export_utils3.c \
			./srcs/execution/builtins/export_utils4.c \
			./srcs/execution/redirections/heredoc.c \
			./srcs/execution/redirections/find_exec.c \
			./srcs/execution/redirections/redirections.c \
			./srcs/execution/exec/execution.c \
			./srcs/execution/exec/execution_utils.c \
			./srcs/execution/exec/execution_sub.c \
			./srcs/execution/exec/exec_builtins.c \
			./srcs/execution/exec/exec_env.c \
			./srcs/execution/exec/close_fd.c \
			./srcs/execution/exec/set_path.c \
			./srcs/utils/error/error.c \
			./srcs/utils/signals/signals.c \
			./srcs/utils/basics/basics.c \
			./srcs/utils/basics/basics1.c \
			./srcs/utils/basics/basics2.c \
			./srcs/utils/basics/split.c \
			./srcs/utils/basics/itoa.c \
			./srcs/utils/display/ascii_art.c \
			./srcs/utils/free/free.c \
			./srcs/utils/free/free1.c \
			./srcs/utils/env/env_init.c \
			./srcs/utils/env/env_keys.c \
			./srcs/utils/env/env_values.c \
			./srcs/utils/env/shell_level.c \
			./srcs/utils/last_ret/last_return.c \
			./srcs/utils/last_ret/last_return1.c \

HEAD		=	./includes/
OBJS		=	${SRC:.c=.o}
INCLUDES	=	./includes/minishell.h

CC			= clang
RM			= rm -rf
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g

READLINE 	= -lreadline

all:		${NAME}

${NAME}:	$(OBJS)
			@${CC} $(CFLAGS) -I${HEAD} -lncurses $(OBJS) -o $(NAME) ${READLINE}
			@echo "${GREEN} Compilation done ${NC}"

%.o: %.c
			@${CC} ${CFLAGS} -I${HEAD} -c $< -o $@

readline:
			sudo apt-get install libreadline-dev
clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			clean all

.PHONY:		all clean fclean re readline
