#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include "termbox.h"
#define CLRS_LEN	13

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "types.h"
#endif

#define RED	0xdd1111
#define BLACK	0x000000
#define YELLOW	0xff7700
#define WHITE	0xffffff

struct tb_cell normcolors[CLRS_LEN] =
{
	// default
	{ ' ',    9, 0 },

	// red/black
	{ 0x2591, 2, 0 },
	{ 0x2592, 2, 0 },
	{ 0x2593, 2, 0 },
	{ 0x2588, 2, 0 },

	// yellow/red
	{ 0x2591, 4, 2 },
	{ 0x2592, 4, 2 },
	{ 0x2593, 4, 2 },
	{ 0x2588, 4, 2 },

	// white/red
	{ 0x2591, 8, 2 },
	{ 0x2592, 8, 2 },
	{ 0x2593, 8, 2 },
	{ 0x2588, 8, 2 },
};

struct tb_cell truecolors[CLRS_LEN] =
{
	// default
	{ ' ',          9, 0 },

	// red/black
	{ 0x2591, RED,  BLACK },
	{ 0x2592, RED,  BLACK },
	{ 0x2593, RED,  BLACK },
	{ 0x2588, RED,  BLACK },

	// yellow/red
	{ 0x2591, YELLOW, RED },
	{ 0x2592, YELLOW, RED },
	{ 0x2593, YELLOW, RED },
	{ 0x2588, YELLOW, RED },

	// white/red
	{ 0x2591, WHITE,  RED },
	{ 0x2592, WHITE,  RED },
	{ 0x2593, WHITE,  RED },
	{ 0x2588, WHITE,  RED },
};

#endif
