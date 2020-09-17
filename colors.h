#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include "termbox.h"

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "stdint.h"
#endif

#define BLACK 0x000000

struct tb_cell normcolors[13] =
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

struct tb_cell truecolors[36] = {
	{ ' ', BLACK, 0x070707 },
	{ ' ', BLACK, 0x1F0707 },
	{ ' ', BLACK, 0x2F0F07 },
	{ ' ', BLACK, 0x470F07 },
	{ ' ', BLACK, 0x571707 },
	{ ' ', BLACK, 0x671F07 },
	{ ' ', BLACK, 0x771F07 },
	{ ' ', BLACK, 0x8F2707 },
	{ ' ', BLACK, 0x9F2F07 },
	{ ' ', BLACK, 0xAF3F07 },
	{ ' ', BLACK, 0xBF4707 },
	{ ' ', BLACK, 0xC74707 },
	{ ' ', BLACK, 0xDF4F07 },
	{ ' ', BLACK, 0xDF5707 },
	{ ' ', BLACK, 0xDF5707 },
	{ ' ', BLACK, 0xD75F07 },
	{ ' ', BLACK, 0xD7670F },
	{ ' ', BLACK, 0xCF6F0F },
	{ ' ', BLACK, 0xCF770F },
	{ ' ', BLACK, 0xCF7F0F },
	{ ' ', BLACK, 0xCF8717 },
	{ ' ', BLACK, 0xC78717 },
	{ ' ', BLACK, 0xC78F17 },
	{ ' ', BLACK, 0xC7971F },
	{ ' ', BLACK, 0xBF9F1F },
	{ ' ', BLACK, 0xBF9F1F },
	{ ' ', BLACK, 0xBFA727 },
	{ ' ', BLACK, 0xBFA727 },
	{ ' ', BLACK, 0xBFAF2F },
	{ ' ', BLACK, 0xB7AF2F },
	{ ' ', BLACK, 0xB7B737 },
	{ ' ', BLACK, 0xCFCF6F },
	{ ' ', BLACK, 0xDFDF9F },
	{ ' ', BLACK, 0xEFEFC7 },
	{ ' ', BLACK, 0xFFFFFF }
};

#endif
