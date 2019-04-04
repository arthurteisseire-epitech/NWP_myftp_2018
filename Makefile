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
DUTILS		=	$(DSRC)utils/
DCOMMANDS	=	$(DSRC)commands/
DSRC_UT		=	tests/

MAIN		=	$(DSRC)main.c		\

SRC		=	$(DSRC)socket.c			\
			$(DSRC)ftp.c			\
			$(DSRC)poll.c			\
			$(DSRC)poll_connection.c	\
			$(DSRC)connection.c		\
			$(DUTILS)safe_alloc.c		\
			$(DUTILS)exit_with.c		\
			$(DUTILS)begin_with.c		\
			$(DUTILS)concat.c		\
			$(DUTILS)find_second_arg.c	\
			$(DCOMMANDS)exec_command.c	\
			$(DCOMMANDS)command_quit.c	\
			$(DCOMMANDS)command_user.c	\
			$(DCOMMANDS)command_pass.c	\
			$(DCOMMANDS)command_cwd.c	\
			$(DCOMMANDS)command_pwd.c	\
			$(DCOMMANDS)command_cdup.c	\
			$(DCOMMANDS)command_list.c	\
			$(DCOMMANDS)command_noop.c	\
			$(DCOMMANDS)command_help.c	\

SRC_UT		=	$(DSRC_UT)poll_test.c		\

CFLAGS		+=	-Wall -Wextra -I$(INC)
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
tests_run: LDFLAGS += -lgcov -lcriterion
tests_run:
	$(CC) -o $(NAME_UT) $(SRC) $(SRC_UT) $(CFLAGS) $(LDFLAGS)
	./$(NAME_UT)
	gcov *.gcno &> /dev/null

tests_debug: CFLAGS += -g
tests_debug: tests_run

.PHONY: all clean fclean re debug tests_run tests_debug
