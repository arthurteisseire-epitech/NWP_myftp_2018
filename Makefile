##
## EPITECH PROJECT, 2018
## PSU_myftp_2018
## File description:
## Makefile
##

CC		=	gcc
INC		=	-Iinclude/
DTESTS		=	tests/
DSRC		=	src/
DUTILS		=	$(DSRC)utils/
DCOMMANDS	=	$(DSRC)commands/

MAIN		=	$(DSRC)main.c		\

SRC		=	$(DSRC)socket.c			\
			$(DSRC)ftp.c			\
			$(DSRC)poll.c			\
			$(DSRC)poll_connection.c	\
			$(DSRC)connection.c		\
			$(DSRC)send_message.c		\
			$(DUTILS)safe_alloc.c		\
			$(DUTILS)exit_with.c		\
			$(DUTILS)begin_with.c		\
			$(DUTILS)concat.c		\
			$(DUTILS)get_path.c		\
			$(DUTILS)find_second_arg.c	\
			$(DUTILS)is_admin.c		\
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
			$(DCOMMANDS)command_pasv.c	\
			$(DCOMMANDS)command_retr.c	\
			$(DCOMMANDS)command_dele.c	\
			$(DCOMMANDS)command_stor.c	\
			$(DCOMMANDS)command_port.c	\

SRC_UT		=	$(DSRC_UT)poll_test.c		\

CFLAGS		+=	-Wall -Wextra $(INC)
OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME		=	myftp

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

.PHONY: all clean fclean re debug
