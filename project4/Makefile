NAME = page

CC = gcc
CFLAG = -g -fsanitize=address
# CFLAG = -Wall -Wextra -Werror

SRC = main.c \
	menu.c \
	utils.c \
	simulate_lfu.c \
	simulate_sc.c \

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
