#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "termbox.h"
#include "types.h"
#include "draw.h"
#include "output.h"
#include "colors.h"

// initialize the framebuffer
void
init ( struct buffer *buf )
{
	// initialize width/height of terminal
	buf->width = tb_width();
	buf->height = tb_height();

	usize len = buf->width * buf->height;
	buf->buf = (u8*) malloc(len);
	len -= buf->width;

	if (buf->buf == NULL) {
		PRINT("fire: cannot ");
		perror("calloc()");
		exit(1);
	}

	// initialize the entire screen to black...
	memset(buf->buf, 0, len);

	// ...except for the last row, which is white.
	// this is the 'base' of the fire.
	memset(buf->buf + len, 12, buf->width);
}

// update the framebuffer
void
dofire ( struct buffer *buf )
{
	usize src;
	usize random;
	usize dest;

	struct tb_cell *realbuf = tb_cell_buffer();

	for (usize x = 0; x < buf->width; ++x)
	{
		for (usize y = 1; y < buf->height; ++y)
		{
			src = y * buf->width + x;
			random = (rand() % 7) & 3;
			dest = src - random + 1;

			if (buf->width > dest)
				dest = 0;
			else
				dest -= buf->width;

			buf->buf[dest] = buf->buf[src] - (random & 1);

			if (buf->buf[dest] > 12)
				buf->buf[dest] = 0;

			realbuf[dest] = colors[buf->buf[dest]];
			realbuf[src]  = colors[buf->buf[src]];
		}
	}
}
