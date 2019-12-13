#
# fire: the pre-cambrian DOOM animation in the terminal
# (c) Kied Llaentenn
# See the LICENSE for more information
#

NAME	= fire
WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Werror

INC	= -Isub/termbox_next/src -Isub/ccommon/

CC	= clang
CFLAGS	= -std=c99 -O3 $(WARNING) $(INC)
LDFLAGS	= -fuse-ld=lld

TRMBOX	= sub/termbox_next/bin/termbox.a
SRC	= main.c draw.c
OBJ	= $(SRC:.c=.o)

all: $(NAME)

clean:
	rm -f $(NAME) $(OBJ)

.c.o:
	@echo "\tCC\t\t$@"
	@$(CC) $(CFLAGS) -c $<

$(TRMBOX):
	@echo "\tCC\t\ttermbox.c"
	@cd sub/termbox_next/ && (make >/dev/null)

$(NAME): $(OBJ) $(TRMBOX)
	@echo "\tLD\t\t$(NAME)"
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

install: $(NAME)
	install -m755 ./$(NAME) /usr/bin/$(NAME)

.PHONY: all clean install
