# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:01:46 by lubenard          #+#    #+#              #
#    Updated: 2019/01/11 12:16:46 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = srcs/main.c \
	  srcs/parsing.c \
	  srcs/utils.c \
	  srcs/optimize.c \
	  srcs/valid_file.c \
	  srcs/valid_file_2.c \
	  srcs/solve.c \
	  srcs/map.c \
	  srcs/make_coord.c \
	  srcs/piece.c \
	  srcs/free.c

OBJ = $(SRC:.c=.o)

CFLAGS = -g3 -Wall -Wextra -Werror

GREEN_OK = "\033[0;32mDONE !\033[00m"

all:  $(NAME)

$(NAME): $(OBJ)
	@cd libft && make
	@clang -o $(NAME) $(CFLAGS) $(OBJ) libft/libft.a -Isrcs/
	@echo fillit ${GREEN_OK}

%.o : %.c
	@clang -c $(CFLAGS) $< -o $@

onlyfillit:
	@clang -o $(NAME) $(CFLAGS) $(SRC) libft/libft.a -Isrcs/
	@echo fillit ${GREEN_OK}

onlylibft:
	@cd libft && make

clean:
	@rm -f $(OBJ)
	@cd libft && make clean
	@echo clean fillit ${GREEN_OK}

fclean: clean
	@rm -f $(NAME)
	@rm -rf fillit.dSYM
	@cd libft && rm -f libft.a
	@echo fclean fillit ${GREEN_OK}

mclean: all clean

cleanexe:
	@rm -f $(NAME)

re: fclean all
