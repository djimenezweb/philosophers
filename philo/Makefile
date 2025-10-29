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
SRCS	=	init.c main.c mutexes.c observer.c philo_routine.c timestamps.c\
			validation.c
OBJDIR	=	objs
OBJS	=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o : %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	rmdir $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
