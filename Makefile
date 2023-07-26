# project
NAME = philo

# compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra -p -g
#-fsanitize=thread


# sources
SRC =	src/main.c \
		src/check_health.c \
		src/libft.c \
		src/lifestyle.c \
		src/mutex_handling.c \
		src/time.c \
		src/structure.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread $^ -o $@

clean :
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME) $(BONUS) *.o

re : fclean all

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^
