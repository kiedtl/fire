/*
 * winsock.h on windows,
 * arpa/inet.h on unix
 * for htons()
 */
#if defined(_WIN32) || defined(__WIN32__)
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "termbox.h"
#include "bool.h"
#include "ff.h"

static uint16_t
clr(uint32_t clr)
{
	uint16_t nclr = (((uint16_t) clr) & 0xff) & 0xffff;
	return nclr | (nclr << 8);
}

void
ff_from_tbscr(uint32_t width, uint32_t height, uint8_t *img, struct tb_cell *colors, FILE *fp)
{
	/* write farbfeld headers */
	fputs("farbfeld", fp);
	uint32_t tmp;
	tmp = htonl(width);
	fwrite(&tmp, sizeof(tmp), 1, fp);
	tmp = htonl(height);
	fwrite(&tmp, sizeof(tmp), 1, fp);

	/* write image row by row */
	uint16_t *rowbuf = malloc(width * (4 * sizeof(uint16_t)));

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			uint32_t color = colors[img[y * width + x]].bg;

			rowbuf[4 * x + 0] = htons(clr(color >> 16));
			rowbuf[4 * x + 1] = htons(clr(color >>  8));
			rowbuf[4 * x + 2] = htons(clr(color));
			rowbuf[4 * x + 3] = htons((uint16_t) 0xffff);
		}

		fwrite(rowbuf, sizeof(uint16_t), width * 4, fp);
		memset(rowbuf, 0, width * (4 * sizeof(uint16_t)));
	}
}
