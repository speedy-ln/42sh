# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcowle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 16:00:34 by kcowle            #+#    #+#              #
#    Updated: 2016/09/05 08:34:29 by knage            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_ifindstr.c 		\
	  ft_strlen2d.c			\
	  ft_strmerge.c			\
	  ft_memset.c			\
	  ft_itoa.c				\
	  ft_bzero.c			\
	  ft_memcpy.c			\
	  ft_memccpy.c			\
	  ft_memmove.c			\
	  ft_memchr.c			\
	  ft_memcmp.c			\
	  ft_strlen.c			\
	  ft_strdup.c			\
	  ft_strcpy.c			\
	  ft_strncpy.c			\
	  ft_strcat.c			\
	  ft_strncat.c			\
	  ft_strlcat.c			\
	  ft_strchr.c			\
	  ft_strstr.c			\
	  ft_strrchr.c			\
	  ft_strnstr.c			\
	  ft_strcmp.c			\
	  ft_strncmp.c			\
	  ft_atoi.c				\
	  ft_isalpha.c			\
	  ft_isdigit.c			\
	  ft_isascii.c			\
	  ft_isalnum.c			\
	  ft_isprint.c			\
	  ft_toupper.c			\
	  ft_tolower.c			\
	  ft_putchar.c			\
	  ft_putchar_fd.c		\
	  ft_putstr.c			\
	  ft_putstr_fd.c		\
	  ft_putendl.c			\
	  ft_putendl_fd.c		\
	  ft_strequ.c			\
	  ft_strnequ.c			\
	  ft_strclr.c			\
	  ft_memalloc.c			\
	  ft_memdel.c			\
	  ft_strnew.c			\
	  ft_strdel.c			\
	  ft_strtrim.c			\
	  ft_strsub.c			\
	  ft_striter.c			\
	  ft_striteri.c			\
	  ft_strmap.c			\
	  ft_strmapi.c			\
	  ft_putnbr.c			\
	  ft_putnbr_fd.c		\
	  ft_strjoin.c			\
	  ft_strsplit.c			\
	  ft_iswhitespace.c		\
	  ft_abs.c				\
	  ft_lstadd.c			\
	  ft_lstnew.c			\
	  get_next_line.c		\
	  ft_isnbr.c			\
	  ft_putnbr_base.c		\
	  ft_put_pf.c			\
	  ft_put_pf2.c			\
	  ft_printf.c			\
	  ft_putwstr.c			\
	  ft_wcslen.c			\
	  ft_putwstr_pf.c		\
	  ft_printf_lib.c		\
	  ft_put_pf3.c			\
	  ft_atoil.c			\
	  ft_findstr.c			\
	  ft_strfcut.c			\
	  ft_strnshift.c		\
	  ft_strrw.c			\
	  ft_strpaste.c			\
	  ft_strnewline.c		\


SRCO = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -c $(CFLAGS) $(SRC)
	@ar rc $(NAME) $(SRCO)
	@ranlib $(NAME)
clean:
	@rm -f $(SRCO)

fclean: clean
	@rm -f $(NAME)

re: fclean all
