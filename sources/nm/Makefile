##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Created by Thomas BLENEAU
##

CC		= gcc

RM		= rm -f

SRCS		= commons/tab.c		\
		commons/error.c	\
		commons/main.c	\
		commons/nm.c		\
		format_32/display.c	\
		format_32/sections.c	\
		format_32/symbols.c	\
		format_32/types.c	\
		format_64/display.c	\
		format_64/sections.c	\
		format_64/symbols.c	\
		format_64/types.c	\

CFLAGS		= -I ../../includes/
CFLAGS		+= -W -Wall -Wextra -std=gnu99

NAME		= ../../my_nm

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
