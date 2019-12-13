#
# fire: the pre-cambrian DOOM animation in the terminal
# (c) Kied Llaentenn
# See the LICENSE for more information
#

NAME	= fire
WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Werror

INC	= -Isub/termbox_next/src

CC	= clang
CFLAGS	= -g -std=c99 $(WARNING) $(INC)
LDFLAGS	= -fuse-ld=lld

SRC	= main.c
OBJ	= $(SRC:.c=.o)
TRMBOX	= sub/termbox_next/bin/termbox.a

all: $(NAME)

clean:
	rm -f $(NAME) $(OBJ)

.c.o:
	@echo "\tCC\t\t$@"
	@$(CC) $(CFLAGS) -c $<

$(TRMBOX):
	@echo "\tCC\t\ttermbox.c"
	@cd sub/termbox_next/ && make

$(NAME): $(OBJ) $(TRMBOX)
	@echo "\tLD\t\t$(NAME)"
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: all clean
