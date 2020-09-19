#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "stdint.h"
#endif

struct buffer {
	size_t width;
	size_t height;
	
	uint8_t* buf;
};

void init(struct buffer *buf, uint16_t width, uint16_t height);
void dofire(struct buffer *buf);
void cleanup(struct buffer *buf);

#endif
