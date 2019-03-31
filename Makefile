##
## EPITECH PROJECT, 2018
## PSU_myftp_2018
## File description:
## Makefile
##

CC			=	gcc
INC			=	include/
DTESTS		=	tests/
DSRC		=	src/
DSRC_UT		=	tests/src/

MAIN		=	$(DSRC)main.c		\

SRC		=	$(DSRC)socket.c		\
			$(DSRC)error.c		\

SRC_UT		=	$(DSRC_UT)tests_socket.c		\

CFLAGS		+=	-Wall -Wextra -I$(INC)
TESTFLAGS	=	-lgtest -lgtest_main
OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME		=	myftp
NAME_UT		=	units

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

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
	$(CC) -o $(NAME_UT) $(SRC) $(SRC_UT) $(CFLAGS) $(TESTFLAGS)
	./$(NAME_UT)
	gcov *.gcno &> /dev/null

tests_debug: CFLAGS += -g
tests_debug: tests_run

.PHONY: all clean fclean re debug tests_run tests_debug
