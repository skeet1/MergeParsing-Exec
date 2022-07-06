# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 07:58:53 by atabiti           #+#    #+#              #
#    Updated: 2022/07/06 16:10:41 by atabiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FALGS = -Wall -Werror -Wextra

HEADER = ./minishell.h \
		./parsing/parse.h \
		./libft/libft.h

SRC = ./exec/builtins.c \
	./exec/ft_env.c \
	./libft/ft_strlen.c  \
	./exec/redirections.c \
	./libft/ft_strnstr.c \
	./exec/ft_unset.c \
	./exec/ft_export.c \
	./exec/ft_others.c \
	./exec/ft_readline.c \
	./exec/ft_init.c  \
	./libft/ft_putchar_fd.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_putendl_fd.c \
	./exec/ftpipe.c \
	./exec/ft_one_command.c \
	./exec/ft_multi_cmds.c   \
	./libft/ft_strdup.c  \
	./libft/ft_atoi.c  \
	./libft/ft_isdigit.c  \
	./exec/ft_here_doc.c \
	./exec/ft_search_path.c \
	./exec/is_builtin.c \
	./exec/ft_exit.c \
	./exec/ftcd.c \
	./exec/ft_copy_1st_env.c \
	./exec/ft_export_tools.c \
	./libft/ft_strncmp.c  \
	./libft/ft_itoa.c  \
	./libft/ft_strjoin.c  \
	./libft/ft_substr.c  \
	./libft/ft_split.c \
	./parsing/ft_check_syntax.c \
	./parsing/ft_token.c \
	./parsing/remove_quotes.c \
	./libft/ft_strlcpy.c \
	./libft/ft_strtrim.c \
	./parsing/parse.c \
	./libft/ft_strcmp.c \
	./parsing/pass_to_exec.c \
	
OBJ = $(SRC:.c=.o)
# ./exec/builtins.o \
# 	./exec/ft_env.o \
# 	./exec/tools.o \
# 	./exec/redirections.o \
# 	./libft/ft_strnstr.o  \
# 	./exec/ft_unset.o \
# 	./exec/ft_export.o \
# 	./exec/ft_others.o \
# 	./exec/ft_readline.o \
# 	./exec/ft_init.o \
# 	./libft/ft_putchar_fd.o \
# 	./libft/ft_putstr_fd.o \
# 	./libft/ft_putendl_fd.o \
# 	./exec/ftpipe.o \
# 	./exec/libft.o \
# 	./exec/ft_one_command.o \
# 	./exec/ft_multi_cmds.o \
# 	./exec/ft_split.o \
# 	./exec/ft_here_doc.o \
# 	./exec/parse.o \
# 	./exec/utils.o \
# 	./exec/ft_search_path.o \
# 	./exec/is_builtin.o \
# 	./exec/ft_exit.o \
# 	./exec/ftcd.o \
# 	./exec/ft_copy_1st_env.o \

define HEADER_G


████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
█░░░░░░██████████░░░░░░█░░░░░░░░░░█░░░░░░██████████░░░░░░█░░░░░░░░░░█░░░░░░░░░░░░░░█░░░░░░██░░░░░░█░░░░░░░░░░░░░░█░░░░░░█████████░░░░░░█████████
█░░▄▀░░░░░░░░░░░░░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀░░░░░░░░░░██░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀░░█░░░░▄▀░░░░█░░▄▀▄▀▄▀▄▀▄▀░░██░░▄▀░░█░░░░▄▀░░░░█░░▄▀░░░░░░░░░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░░░░░█░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░░░░░▄▀░░░░░░▄▀░░███░░▄▀░░███░░▄▀░░░░░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░█████████░░▄▀░░██░░▄▀░░█░░▄▀░░█████████░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░░░░░░░░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░░░░░░░░░█░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░██░░░░░░██░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░██░░▄▀░░███░░▄▀░░███░░░░░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░░░░░░░░░█░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░██████████░░▄▀░░███░░▄▀░░███░░▄▀░░██░░▄▀░░░░░░▄▀░░███░░▄▀░░███████████░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░█████████░░▄▀░░█████████░░▄▀░░█████████
█░░▄▀░░██████████░░▄▀░░█░░░░▄▀░░░░█░░▄▀░░██░░▄▀▄▀▄▀▄▀▄▀░░█░░░░▄▀░░░░█░░░░░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░░░░░█░░▄▀░░░░░░░░░░█░░▄▀░░░░░░░░░░█
█░░▄▀░░██████████░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀░░██░░░░░░░░░░▄▀░░█░░▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█
█░░░░░░██████████░░░░░░█░░░░░░░░░░█░░░░░░██████████░░░░░░█░░░░░░░░░░█░░░░░░░░░░░░░░█░░░░░░██░░░░░░█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█
████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████

endef
export	HEADER_G

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FALGS) $(OBJ) -lreadline -L /goinfre/$(USER)/.brew/opt/readline/lib -I 	/goinfre/$(USER)/.brew/opt/readline/include -o $(NAME)
	@echo "\033[1;31m$$HEADER_G"
	@echo "\033[0;32m \033[1m minishell is created successfully\033[0m"
clean :
	rm $(OBJ)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m"
	
fclean : clean
	rm $(NAME)
	@echo "\033[0;31m>> $(NAME) is deleted.\033[0m"

re : fclean all

