#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpiven <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 20:30:46 by tpiven            #+#    #+#              #
#    Updated: 2018/01/23 20:30:51 by tpiven           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =  libftprintf.a

FLAGS = -Wall -Wextra -Werror 

PRINTF_DIR = ft_printf

LIB_DIR = libft

OBJ_DIR = $(LIB_DIR) $(PRINTF_DIR)

HEADERS = -I.
PRINTF_SRC = ft_printf.c parse.c print.c wchar.c handle.c handle_spec.c
LIB_SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
		ft_number_word.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c \
		ft_putendl.c ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c \
		ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
		ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
		ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
		ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstadd.c ft_lstdel.c \
		ft_lstdelone.c ft_lstiter.c ft_lstnew.c ft_lstmap.c ft_lstclean.c \
		ft_lstsize.c ft_lstadd_end.c ft_lstlast.c ft_putnstr.c ft_itoa_base.c\
		ft_newstr.c ft_putwchar.c ft_putwstr.c

PRINTF_OBJ = $(addprefix $(PRINTF_DIR)/,$(PRINTF_SRC:.c=.o))
LIB_OBJ = $(addprefix $(LIB_DIR)/,$(LIB_SRC:.c=.o))

all:	$(NAME)

$(OBJ_DIR)/%.o:		$(LIB_DIR)/%.c $(PRINTF_DIR)/%.c
	@gcc $(FLAGS) -c $? $(FLAGS) $(HEADERS)

$(NAME):	$(PRINTF_OBJ) $(LIB_OBJ)
	@ar rc $(NAME) $(PRINTF_OBJ) $(LIB_OBJ)
	@ranlib $(NAME)
	
clean:
	@/bin/rm -f $(PRINTF_OBJ) $(LIB_OBJ)
	
fclean:		clean
	@/bin/rm -f $(NAME)

re:			fclean	all

.PHONY: clean all fclean re
