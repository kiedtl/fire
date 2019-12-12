#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define BOOL	unsigned char
#define TRUE	1
#define FALSE	0
#define PRINT(...)	fprintf(stderr, __VA_ARGS__);

// I miss the Rust type system :(
typedef uint8_t		 u8;
typedef uint16_t	u16;
typedef uint32_t	u32;

#if UINTPTR_MAX == 0xffff
typedef uint16_t	usize;
#elif UINTPTR_MAX == 0xffffffff
typedef uint32_t	usize;
#elif UINTPTR_MAX == 0xffffffffffffffff
typedef uint64_t	usize;
#endif


char esc = (char) 27;
usize width;
usize height;
usize palette[] = { 0x00, 0xff0000, 0xff6611, 0xffff66, 0xffffff };
usize *pixels;

void dofire ( void );
void draw ( void );

int
main ( void )
{
	// populate width and height
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	width = w.ws_row;
	height = w.ws_col;

	pixels = (usize*) calloc((width * height), sizeof(usize));

	// init pixels
	for (usize i = 0; i < width; i++)
	{
		pixels[((width * height) - width) + i] = palette[4];
	}

	dofire();
	return 0;
}

void
dofire ( void )
{
	for (usize x = 0; x < width; x++)
	{
		for (usize y = 0; y < height; y++)
		{
			usize src = y * width + x;
			usize random = (rand() % 7) & 3;
			usize dest = src - random + 1;
			usize color;

			if (width > dest ) dest = 0;
			else dest -= width;

			pixels[dest] = pixels[src] - (random & 1);
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
	for (usize x = 0; x < width; x++)
	{
		for (usize y = 0; y < height; y++)
		{
			usize color = pixels[y * width + x];
			u8 blue = color % 256;
			u8 green = ((color - blue) / 256) % 256;
			u8 red = ((color - blue) / (int)pow((double)256, (double)2))-(green / 256);

			PRINT("%c[48;2;%i;%i;%im %c[0m", esc, red, blue, green, esc);
		}
		PRINT("\n");
	}
}
