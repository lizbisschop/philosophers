NAME = philo

SRCS =  main.c dead_or_alive.c eat_sleep_think.c \
print_stuff.c threading.c utils.c \
set_struct.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I philo.h

all: $(NAME)

ifdef DEBUG
FLAGS += -fsanitize=address
endif

$(NAME): $(OBJ)
	gcc $(FLAGS) -pthread $(INCLUDES) $^ -o $@ -g 
# $(OBJ):
# 	gcc -Wall -Werror -Wextra -c $(SRCS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all