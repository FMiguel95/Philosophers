NAME = philo

SRC = main.c parse_args.c printer.c philo_thread.c philo_utils.c \
		philo_eat_sequence.c philo_log.c get_current_time.c setup_cleanup.c \
		watcher_thread.c
BIN = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread
RM = rm -rf

all: $(NAME)

$(NAME): $(BIN)
	$(CC) $(CFLAGS) -lpthread $(BIN) -o $(NAME)

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all
