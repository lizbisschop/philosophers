NAME = philo

SRCS =  main.c dead_or_alive.c eat_sleep_think.c \
eating.c print_stuff.c threading.c utils.c

OBJ = $(SRCS:.c=.o)

INCLUDES = -I philo.h

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra -pthread $(INCLUDES) $^ -o $@
# $(OBJ):
# 	gcc -Wall -Werror -Wextra -c $(SRCS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all