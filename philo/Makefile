# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 09:07:40 by danielji          #+#    #+#              #
#    Updated: 2025/10/24 09:08:01 by danielji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philosophers
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	=	atoi.c cleanup.c errors.c initialization.c main.c threads.c \
			timestamps.c validation.c
OBJS	=	$(SRCS:.c=.o)
ARGS	=	5 800 200 200

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

run : all
	./$(NAME) $(ARGS)

check : all
	valgrind ./$(NAME) $(ARGS)

.PHONY : all clean fclean re run check