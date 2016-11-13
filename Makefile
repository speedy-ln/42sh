# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcowle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 15:59:15 by kcowle            #+#    #+#              #
#    Updated: 2016/09/10 13:42:47 by knage            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = clang

SRC =	bquote2.c			\
		bquote.c			\
		extras2.c			\
		old.c				\
		printline.c			\
		ft_builtin_support.c\
        init.c              \
        ft_cd_support.c     \
        file_arf.c			\
		cut_copy_paste.c	\
		non_canonical1.c	\
	  	non_canonical2.c	\
		non_canonical3.c    \
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
	   	quote.c				\
	   	builtin.c			\
	   	shell.c				\
		ft_excve.c			\
		redirection.c		\
		vars.c				\
		variables.c			\
		libft/libft.a		\
        tab_support.c		\
        tab_support1.c		\
        tab_support2.c		\
		tab_support3.c		\
		key_hook.c			\
		key_hook_support.c	\
		cut_copy_paste_key.c\
		get_line.c			\
		print.c				\
		return.c			\
		vars2.c				\
		get_dir.c			\
		env.c				\
		redirect_heredoc.c  \
		redirection_support.c   \
		redirection_support2.c   \

all: $(NAME)

$(NAME):
	@echo "compiling libft..."
	@make re -C libft/
	@echo "compiling program..."
	@$(CC) -o $(NAME) $(SRC) -ltermcap -g
	@echo "done! :D"

#@gcc -g $(SRC) -ltermcap

clean:
	@make clean -C libft/

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re: fclean all

run: re 
	@echo "running program"
	./$(NAME)
