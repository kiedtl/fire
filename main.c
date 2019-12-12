#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#include "termbox.h"
#include "bool.h"
#include "outp.h"
#include "type.h"

#define STEPS	13

void init ( struct term_buf buf );
void dofire ( void );
void draw ( void );

int
main ( void )
{
	// initialize termbox
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	struct term_buf buf;
	draw_init(&buf);

	// initialize drawing
	

	draw();
	dofire();

	// cleanup termbox
	tb_shutdown();

	return 0;
}

void
init ( struct term_buf buf )
{
	buf->init_width = buf->width;
	buf->init_height = buf->height;

	usize len = buf->width * buf->height;
	buf->tmp_buf = malloc(len);
	len -= buf->width;

	if (buf->tmp_buf == NULL)
		PRINT("fire: error: unable to malloc() memory for buffer\n");

	memset(buf->tmp_buf, 0, len);
	memset(buf->tmp_buf + len, STEPS - 1, buf->width);
}

void
dofire ( void )
{
	for (usize x = 0; x < width; x++)
	{
		for (usize y = 0; y < height; y++)
		{
			usize src = y * width + x;
			usize random = 0;//(rand() % 7) & 3;
			usize dest = src - random + 1;
			usize color;

			if (width > dest ) dest = 0;
			else dest -= width;

			color = pixels[src];

			if (color == 0 || color == (usize) NULL)
				pixels[(src - width) % ((width * height) - 1)] = palette[0];
			else
				pixels[(dest - width) % ((width * height) - 1)] = pixels[src] - (random & 1);
			draw();
		}
	}
}

void
draw ( void )
{
	// clear screen
	PRINT("%c[2J", esc);

	// draw pixels onto screen
	for (usize y = 0; y < height; y++)
	{
		for (usize x = 0; x < width; x++)
		{
			usize color = pixels[y * width + x];
			if (color == (usize) NULL) continue;

			// extract RGB value from color
			u8 blue = color % 256;
			u8 green = ((color - blue) / 256) % 256;
			u8 red = ((color - blue) / (int)pow((double)256, (double)2))-(green / 256);

			PRINT("%c[48;2;%i;%i;%im %c[0m", esc, red, blue, green, esc);
		}
		PRINT("\n");
	}
}
