##
## EPITECH PROJECT, 2018
## ftp
## File description:
## Makefile
##

CC		=	gcc
INC		=	include/
DTESTS		=	tests/
DSRC		=	src/
DSRC_UT		=	tests/src/

SRC		=	$(DSRC)file.c			\

SRC_UT		=	$(DSRC_UT)tests_file.c		\

CFLAGS		+=	-Wall -Wextra -I$(INC)
LDFLAGS		=	-lgtest -lgtest_main
OBJ		=	$(SRC:.c=.o)
NAME		=	myftp
NAME_UT		=	units

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_UT)

re: fclean all

debug: CFLAGS += -g
debug: re

tests_run: CFLAGS += --coverage
tests_run: LDFLAGS += -lgcov
tests_run:
	$(CC) -o $(NAME_UT) $(SRC) $(SRC_UT) $(CFLAGS) $(LDFLAGS)
	./$(NAME_UT)
	gcov *.gcno &> /dev/null

tests_debug: CFLAGS += -g
tests_debug: tests_run

.PHONY: all clean fclean re debug tests_run tests_debug
