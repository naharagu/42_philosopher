CC			=	gcc
C_FLAGS 	=	-Wall -Werror -Wextra -pthread
NAME		=	philo
SRCS		= 	main.c \
				validate.c \
				init.c \
				utils.c \
				control_philo.c \
				monitor_philo.c
OBJS_DIR	=	./obj/
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -o $@ -c $<

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
