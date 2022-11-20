NAME = a.out

CC = gcc
CFLAG = -Wall -Wextra -Werror -fsanitize=address -g

SRC = main.c \
	menu.c \
	utils.c \
	simulate/fifo.c \
	simulate/lru.c \
	simulate/lifo.c \
	simulate/lfu.c \
	simulate/optimal.c \
	simulate/sc.c \
	simulate/esc.c

OBJ = $(SRC:%.c=%.o)

RM = rm -f

all: $(NAME)
.PHONY: all

$(NAME):	$(OBJ)
	$(CC) $(CFLAG) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJ)
.PHONY: clean

fclean: clean
	$(RM) $(NAME)
.PHONY: fclean

re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: re
