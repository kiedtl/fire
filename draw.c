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
init(struct buffer *buf, uint16_t width, uint16_t height)
{
	// initialize width/height of terminal
	buf->width = width;
	buf->height = height;

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
	memset(buf->buf + len, opts->truecolor ? 34 : 12, buf->width);
}

// update the framebuffer
void
dofire(struct buffer *buf)
{
	size_t src;
	size_t rnd_wind = (lrand48() % 7) & 3;
	size_t rnd_lose = lrand48() % 100;
	size_t rnd_loss = (lrand48() % 7) & 3;
	size_t dest;

	struct tb_cell *realbuf = tb_cell_buffer();

	for (size_t x = 0; x < buf->width; ++x) {
		for (size_t y = 1; y < buf->height; ++y) {
			// TODO; test rngs
			if ((lrand48() % opts->random_factor) == 0) {
				rnd_wind = (lrand48() % 7) & 3;
				rnd_lose = lrand48() % 100;
				rnd_loss = (lrand48() % 7) & 3;
			}

			src = y * buf->width + x;

			if (opts->random_wind) {
				dest = src - rnd_wind + opts->wind;
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

			size_t loss = rnd_lose < opts->heat_loss ? 2 : 0;
			buf->buf[dest] = MAX(buf->buf[src] - (rnd_loss & loss), 0);

			if (buf->buf[dest] > max_value) {
				buf->buf[dest] = 0;
			}

			// TODO: comment everything

			// copy from our buffer to termbox's buffer
			// unless, of course, our buffer is bigger
			if (src >= tb_width() * tb_height()) {
				continue;
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
}
