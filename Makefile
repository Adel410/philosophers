# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 18:49:29 by ahadj-ar          #+#    #+#              #
#    Updated: 2024/10/22 17:25:31 by ahadj-ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###	NAME ###

NAME	= philo

### SOURCES	###

FILES	=	srcs/main.c \
			srcs/parsing.c \
			srcs/philosophers.c \
			srcs/big_brother.c \
			srcs/init_and_cleanup.c \
			srcs/thread_tools.c \
			srcs/tools.c \
			srcs/tools2.c \
			srcs/tools3.c \


INCLUDE	= 	include/philo.h

### MACROS ###

CC	= cc

CFLAGS	= -g -Wall -Werror -Wextra

OBJ	= $(FILES:.c=.o)

### RULES ###

all	: $(NAME)
		@cat display.txt

$(NAME)	: $(OBJ) $(INCLUDE)
		$(CC) $(OBJ) -o  $(NAME) 

clean:
		rm -f $(OBJ)

fclean:
		rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY:	clean fclean re                                  
