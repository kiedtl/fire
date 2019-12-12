#
# fire: the pre-cambrian DOOM animation in the terminal
# (c) Kied Llaentenn
# See the LICENSE for more information
#

NAME	= fire
WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Werror

SRCDIR	= src
SUBDIR	= sub

INC	= -I$(SUBDIR)/termbox_next/

CC	= clang
CFLAGS	= -g -std=c99 $(WARNING) $(INC)
LDFLAGS	= -fuse-ld=lld

SRC	= main.c
OBJ	= $(SRC:.c=.o)

all: $(NAME)

clean:
	rm -f $(SRCDIR)/$(NAME) $(SRCDIR)/$(OBJ)

.c.o:
	@echo "\tCC\t\t$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCDIR)/$(OBJ)
	@echo "\tLD\t\t$(NAME)"
	@$(CC) -o $(SRCDIR)/$@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: all clean
