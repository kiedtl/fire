// colors.h: defines the colors for the fire.
// feel free to modify to customize the look of the animation. :)
// structure: <unicode hex value>, <foreground>, <background>

#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include "termbox.h"

struct tb_cell colors[13] =
{
	{ ' ',    9, 0 },
	{ 0x2591, 2, 0 },
	{ 0x2592, 2, 0 },
	{ 0x2593, 2, 0 },
	{ 0x2588, 2, 0 },
	{ 0x2591, 4, 2 },
	{ 0x2592, 4, 2 },
	{ 0x2593, 4, 2 },
	{ 0x2588, 4, 2 },
	{ 0x2591, 8, 4 },
	{ 0x2592, 8, 4 },
	{ 0x2593, 8, 4 },
	{ 0x2588, 8, 4 },
};

#endif
