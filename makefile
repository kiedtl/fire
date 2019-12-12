#
# fire: the pre-cambrian DOOM animation in the terminal
# (c) Kied Llaentenn
# See the LICENSE for more information
#

NAME	= fire
WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Werror

CC	= clang
CFLAGS	= -g -O3 -std=c99 $(WARNING)
LDFLAGS	= -fuse-ld=lld

SRC	= main.c
OBJ	= $(SRC:.c=.o)

all: $(NAME)

clean:
	rm -f $(NAME) $(OBJ)

.c.o:
	@echo "\tCC\t\t$@"
	@$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJ)
	@echo "\tLD\t\t$(NAME)"
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: all clean
