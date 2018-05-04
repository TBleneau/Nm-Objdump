##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Created by Thomas BLENEAU
##

CC		= gcc

RM		= rm -f

SRCS		= commons/error.c	\
		commons/main.c	\
		commons/objdump.c	\
		commons/options.c	\
		commons/tab.c		\
		format_32/content.c	\
		format_32/flags.c	\
		format_32/headers.c	\
		format_32/sections.c	\
		format_64/content.c	\
		format_64/flags.c	\
		format_64/headers.c	\
		format_64/sections.c	\

CFLAGS		= -I ../../includes/
CFLAGS		+= -W -Wall -Wextra -std=gnu99

NAME		= ../../my_objdump

OBJS		= $(SRCS:.c=.o)

CLEAN		= clean

FCLEAN		= fclean

RUN		= tests_run

$(NAME)		: $(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all		: $(NAME)

$(RUN)		: all
		./$(NAME)

$(CLEAN)	:
		$(RM) $(OBJS)

$(FCLEAN)	: $(CLEAN)
		$(RM) $(NAME)

re		: $(FCLEAN) all

.PHONY : all $(CLEAN) $(FCLEAN) $(RUN) re
