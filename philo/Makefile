#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 09:07:40 by danielji          #+#    #+#              #
#    Updated: 2025/10/26 15:34:13 by danielji         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	philosophers
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	=	cleanup.c initialization.c main.c observer.c\
			philo_routine.c timestamps.c validation.c
OBJDIR	=	objs
OBJS	=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
ARGS	=	6 800 200 200

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o : %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	rmdir $(OBJDIR)
	clear

fclean : clean
	rm -f $(NAME)

re : fclean all

run : $(NAME)
	@echo 'make run ARGS="$(ARGS)"'
	./$(NAME) $(ARGS)

check : $(NAME)
	valgrind --leak-check=full ./$(NAME) $(ARGS)

.PHONY : all clean fclean re run check
