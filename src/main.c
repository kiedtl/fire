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

	width = w.ws_col;
	height = w.ws_row;

	pixels = (usize*) calloc((width * height), sizeof(usize));

	// init pixels
	for (usize c = 0; c < (width * height); c++) pixels[c] = (usize) NULL;
	for (usize i = 0; i < width; i++)
	{
		pixels[((width * (height - 1)) - width) + i] = palette[4];
	}

	draw();
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
