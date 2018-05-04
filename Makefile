##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Created by Thomas BLENEAU
##

MK		= make

RUN		= tests_run

CLEAN		= clean

FCLEAN		= fclean

all		:
		$(MK) -s -C ./sources/nm/
		$(MK) -s -C ./sources/objdump/

nm		:
		$(MK) -s -C ./sources/nm/

objdump		:
		$(MK) -s -C ./sources/objdump/

$(CLEAN)	:
		$(MK) $(CLEAN) -s -C ./sources/nm/
		$(MK) $(CLEAN) -s -C ./sources/objdump/

$(FCLEAN)	: $(CLEAN)
		$(MK) $(FCLEAN) -s -C ./sources/nm/
		$(MK) $(FCLEAN) -s -C ./sources/objdump/

$(RUN)	:
	$(MK) $(RUN) -C ./sources/nm/
	$(MK) $(RUN) -C ./sources/objdump/

re: $(FCLEAN) all

.PHONY: all nm objdump $(CLEAN) $(FCLEAN) $(RUN) re
