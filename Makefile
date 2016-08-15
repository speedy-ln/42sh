# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcowle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 15:59:15 by kcowle            #+#    #+#              #
#    Updated: 2016/08/15 07:16:41 by knage            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = clang -Wall -Wextra -Werror

SRC =	file_arf.c			\
		cut_copy_paste.c	\
		non_canonical1.c	\
	  	non_canonical2.c	\
	  	non_canonical.c		\
	  	free.c				\
	   	signals.c			\
	   	history.c			\
	   	fdfuncs.c			\
	   	pipes.c				\
	   	new.c				\
		main.c				\
	  	extras.c			\
	   	func.c				\
	   	help.c				\
	   	echo.c				\
	   	non_canonical3.c	\
	   	quote.c				\
	   	builtin.c			\
	   	shell.c				\
		ft_excve.c			\
		redirection.c		\
		libft/libft.a		\

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling libft..."
	@make re -C libft/
	@echo "compiling program..."
	@$(CC) -o $(NAME) $(SRC) -ltermcap
	@echo "done! :D"

clean:
	@make clean -C libft/

fclean: clean
	@make fclean -C libft/
	@rm $(NAME)

re: fclean all

run: re 
	./$(NAME)
