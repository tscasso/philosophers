NAME = philosophers

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

HEADERS = philosophers.h

SRCS =	main.c \
		init.c \
		parsing.c \
		routine.c \
		error.c \
		utils.c \
		philo_routines.c \
		check_functions.c \

OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(SRCS)
	@echo "Compilation en cours..."
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Compilation terminée!"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(OBJS)

re: fclean all

fclean: clean

.PHONY: all clean re fclean