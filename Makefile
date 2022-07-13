# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 07:58:53 by atabiti           #+#    #+#              #
#    Updated: 2022/07/13 08:56:40 by atabiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFALGS = 
# -Wall -Werror -Wextra
SRC = ./exec/builtins.c \
	./exec/ft_env.c \
	./libft/ft_strlen.c  \
	./exec/redirections.c \
	./libft/ft_strnstr.c \
	./exec/ft_unset.c \
	./exec/ft_export.c \
	./exec/ft_others.c \
	./exec/ft_init.c  \
	./libft/ft_putchar_fd.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_putendl_fd.c \
	./libft/ft_tolower.c \
	./exec/ftpipe.c \
	./exec/ft_one_command.c \
	./exec/ft_multi_cmds.c   \
	./libft/ft_strdup.c  \
	./libft/ft_atoi.c  \
	./libft/ft_isdigit.c  \
	./libft/ft_tolower.c \
	./libft/ft_calloc.c \
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
	./exec/pass_to_exec.c \
	./parsing/ft_check_syntax.c  \
	./exec/ft_builtcheck.c \
	./exec/ft_heredoc_tools.c \
	 
OBJ = builtins.o \
	 ft_env.o \
	 ft_strlen.o  \
	 redirections.o \
	 ft_strnstr.o \
	 ft_unset.o \
	 ft_export.o \
	 ft_others.o \
	 ft_init.o  \
	 ft_putchar_fd.o \
	 ft_putstr_fd.o \
	 ft_putendl_fd.o \
	 ft_tolower.o\
	 ftpipe.o \
	 ft_one_command.o \
	 ft_calloc.o \
	 ft_multi_cmds.o   \
	 ft_strdup.o  \
	 ft_atoi.o  \
	 ft_isdigit.o  \
	 ft_here_doc.o \
	 ft_search_path.o \
	 is_builtin.o \
	 ft_exit.o \
	 ftcd.o \
	 ft_copy_1st_env.o \
	 ft_export_tools.o \
	 ft_strncmp.o  \
	 ft_itoa.o  \
	 ft_strjoin.o  \
	 ft_substr.o  \
	 ft_split.o \
	 ft_check_syntax.o \
	 ft_token.o \
	 remove_quotes.o \
	 ft_strlcpy.o \
	 ft_strtrim.o \
	 parse.o \
	 ft_strcmp.o \
	 pass_to_exec.o \
	ft_builtcheck.o \
	ft_heredoc_tools.o \
	
all : $(NAME)
$(OBJ) :
	 $(CC) $(CFALGS) -c $(SRC) 

$(NAME) : $(OBJ)
	$(CC)  $(OBJ) -o $(NAME)  -lreadline -L /goinfre/$(USER)/.brew/opt/readline/lib -I 	/goinfre/$(USER)/.brew/opt/readline/include 

clean :
	rm -f *.o	
	
fclean : clean
	rm $(NAME)

re : fclean all
