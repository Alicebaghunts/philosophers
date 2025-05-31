NAME = philo_bonus
SRC_DIR = src
INC_DIR = includes

SRC = $(shell find . -name "*.c")

OBJ = $(SRC:.c=.o)

CC = cc 

CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

echo:
	@echo $(OBJ)

.PHONY: all clean fclean re
