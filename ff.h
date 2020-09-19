#ifndef FF_H
#define FF_H

#include <stdio.h>
#include <stdint.h>
#include "termbox.h"
#include "bool.h"

void ff_from_tbscr(
	uint32_t width, uint32_t height,
	uint8_t *img, struct tb_cell *colors,
	FILE *fp
);

#endif
