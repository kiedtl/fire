#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED
#include "types.h"

typedef struct buffer
{
	usize width;
	usize height;
	
	u8* buf;
} buffer;

void init ( struct buffer *buf );
void dofire ( struct buffer *buf );

#endif
