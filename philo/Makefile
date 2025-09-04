NAME		= philosophers
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
SRC_PATH	= src/
SRC			=	atoi.c \
				cleanup.c \
				errors.c \
				initialization.c \
				main.c \
				threads.c \
				timestamps.c \
				validation.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -I./includes
ARGS		= 5 800 200 200

all : $(NAME)
	@echo "============== Done ============="

$(NAME) : $(OBJS)
	@echo "=========== Compiling ==========="
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@echo "===== Creating object files ====="
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	@echo "======= Removing .o files ======="
	@rm -f $(OBJS)

fclean : clean
	@echo "=== Removing philo executable ==="
	@rm -f $(NAME)

re : fclean all
	@echo "=========== Rebuilding =========="

run : all
	@$(MAKE) clean
	./$(NAME) $(ARGS)

check : all
	valgrind ./$(NAME) $(ARGS)

.PHONY : all clean fclean re run check