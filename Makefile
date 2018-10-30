# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelek <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 16:54:30 by gmelek            #+#    #+#              #
#    Updated: 2018/05/02 14:08:55 by gmelek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell
SRC_PATH = srcs
OBJ_PATH = objs
CPPFLAGS = -Iincludes
LDFLAGS = -Llibft
LDLIBS = -lft
LDFGNL = -Lgnl
LDGNL = -gnl
CC = clang
INC = includes
CFLAGS = -g -v -Wall -Werror -Wextra
SRC_NAME = main.c \
		   tools.c\
		   setenv.c\
		   mem_free.c\
		   signal.c\
		   exec_arg.c\
		   error.c\
		   list.c\
		   cd.c\
	gnl/get_next_line.c


SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
#OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ= $(SRC:.c=.o)

all : $(NAME)
$(NAME): $(OBJ)
	@echo "\033[92mCOMPILE\033[0m"
	make -C libft/
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS)  -I $(INC) -o $(NAME) $(LDLIBS) $(LDFGNL)
	@echo "\033[92mSUCCES COMPILE\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(INC) -o $@ -c $<

clean:
	@echo "\033[92mCLEAN\033[0m"
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	@echo "\033[92mFCLEAN\033[0m"
	make -C libft/ fclean
	rm -fv $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
