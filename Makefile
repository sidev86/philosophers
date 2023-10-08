NAME = philo

INC = philo.h

SRC =	main.c\
		args_check.c\
		init.c\
		threads.c\
 		errors.c\
		routine.c\
		monitor.c\
		forks.c\
		utils.c

CC = gcc

FLAGS = -g -Wall -Wextra -Werror -pthread

OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
