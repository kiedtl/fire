#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "termbox.h"
#include "bool.h"
#include "outp.h"
#include "type.h"

#define STEPS	13

typedef struct term_buf
{
	usize width;
	usize height;
	usize init_width;
	usize init_height;

	u8* tmp_buf;
} term_buf;

void init ( struct term_buf *buf );
void dofire ( struct term_buf *term_buf );

int
main ( void )
{
	// initialize termbox
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();
	struct term_buf buf;
	
	// initialize drawing
	buf.width = tb_width();
	buf.height = tb_height();
	init(&buf);

	// animate
	while (TRUE)
	{
		tb_clear();
		dofire(&buf);
		tb_present();
	}

	// cleanup termbox
	tb_shutdown();
	free(buf.tmp_buf);

	return 0;
}

void
init ( struct term_buf *buf )
{
	buf->init_width = buf->width;
	buf->init_height = buf->height;

	usize len = buf->width * buf->height;
	buf->tmp_buf = (u8*) malloc(len);
	len -= buf->width;

	if (buf->tmp_buf == NULL) {
		PRINT("fire: cannot ");
		perror("calloc()");
		exit(1);
	}
	
	memset(buf->tmp_buf, 0, len);
	memset(buf->tmp_buf + len, STEPS - 1, buf->width);
}

void
dofire ( struct term_buf *term_buf )
{
	static struct tb_cell fire[STEPS] =
	{
		{' ', 9, 0}, // default
		{0x2591, 2, 0}, // red
		{0x2592, 2, 0}, // red
		{0x2593, 2, 0}, // red
		{0x2588, 2, 0}, // red
		{0x2591, 4, 2}, // yellow
		{0x2592, 4, 2}, // yellow
		{0x2593, 4, 2}, // yellow
		{0x2588, 4, 2}, // yellow
		{0x2591, 8, 4}, // white
		{0x2592, 8, 4}, // white
		{0x2593, 8, 4}, // white
		{0x2588, 8, 4}, // white
	};

	usize src;
	usize random;
	usize dst;

	usize w = term_buf->init_width;
	u8* tmp = term_buf->tmp_buf;

	if ((term_buf->width != term_buf->init_width) || (term_buf->height != term_buf->init_height))
	{
		return;
	}

	struct tb_cell* buf = tb_cell_buffer();

	for (usize x = 0; x < w; ++x)
	{
		for (usize y = 1; y < term_buf->init_height; ++y)
		{
			src = y * w + x;
			random = ((rand() % 7) & 3);
			dst = src - random + 1;

			if (w > dst)
			{
				dst = 0;
			}
			else
			{
				dst -= w;
			}

			tmp[dst] = tmp[src] - (random & 1);

			if (tmp[dst] > 12)
			{
				tmp[dst] = 0;
			}

			buf[dst] = fire[tmp[dst]];
			buf[src] = fire[tmp[src]];
		}
	}

}

			// extract RGB value from color
			//u8 blue = color % 256;
			//u8 green = ((color - blue) / 256) % 256;
			//u8 red = ((color - blue) / (int)pow((double)256, (double)2))-(green / 256);
