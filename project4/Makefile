NAME = a.out

CC = gcc
CFLAG = -fsanitize=address -g
# CFLAG = -Wall -Wextra -Werror

SRC = main.c \
	menu.c \
	utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
.PHONY: all

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: re
