NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
SRC_PATH	= src/
SRC			=	atoi.c \
				initialization.c \
				main.c \
				threads.c \
				timestamps.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -I./includes

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "=== Compiling ==="
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@echo "=== Creating object files ==="
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	@echo "=== Removing .o files ==="
	@rm -f $(OBJS)

fclean : clean
	@echo "=== Removing philo executable ==="
	@rm -f $(NAME)

re : fclean all
	@echo "=== Rebuilding ==="

run : all
	@$(MAKE) clean
	./$(NAME) 10 20 30 40 50

check : all
	valgrind ./$(NAME) 10 20 30 40 50

.PHONY : all clean fclean re run check