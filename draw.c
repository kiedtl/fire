#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "termbox.h"
#include "draw.h"
#include "colors.h"
#include "output.h"

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "stdint.h"
#endif

#define MAX(VAL1, VAL2)    ((VAL1) > (VAL2) ? (VAL1) : (VAL2))
#define MIN(VAL1, VAL2)    ((VAL1) < (VAL2) ? (VAL1) : (VAL2))

// arguments
extern struct Options *opts;

// initialize the framebuffer
void
init(struct buffer *buf)
{
	// initialize width/height of terminal
	buf->width = tb_width();
	buf->height = tb_height();

	size_t len = buf->width * buf->height;
	buf->buf = (uint8_t*) calloc(len, sizeof(uint8_t));
	len -= buf->width;

	if (buf->buf == NULL) {
		EPRINT("fire: cannot ");
		perror("calloc()");
		exit(1);
	}

	// calloc sets the entire screen to black
	// ...except for the last row, which is white.
	// this is the 'base' of the fire.
	memset(buf->buf + len, opts->truecolor ? 35 : 12, buf->width);
}

// update the framebuffer
void
dofire(struct buffer *buf)
{
	size_t src;
	size_t random = (rand() % 7) & 3;
	size_t dest;

	struct tb_cell *realbuf = tb_cell_buffer();

	for (size_t x = 0; x < buf->width; ++x) {
		for (size_t y = 1; y < buf->height; ++y) {
			if ((rand() % opts->random_factor) == 0) {
				random = (rand() % 7) & 3;
			}

			src = y * buf->width + x;

			if (opts->random_wind) {
				dest = src - random + opts->wind;
			} else {
				dest = src + opts->wind;
			}

			size_t max_value;
			struct tb_cell *colors;
			if (opts->truecolor == TRUE) {
				colors = (struct tb_cell*) &truecolors;
				max_value = 35;
			} else {
				colors = (struct tb_cell*) &normcolors;
				max_value = 12;
			}

			if (buf->width > dest) {
				dest = 0;
			} else {
				dest -= buf->width;
			}

			size_t loss = MIN(opts->max_heat_loss, 3);
			buf->buf[dest] = MAX(buf->buf[src] - (random & loss), 0);

			if (buf->buf[dest] > max_value) {
				buf->buf[dest] = 0;
			}

			realbuf[dest] = colors[buf->buf[dest]];
			realbuf[src]  = colors[buf->buf[src]];
		}
	}
}


// free framebuffer and shutdown termbox
void
cleanup(struct buffer *buf)
{
	free(buf->buf);
	tb_shutdown();
}
