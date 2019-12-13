#include <stdlib.h>

#include "bool.h"
#include "output.h"
#include "draw.h"
#include "types.h"
#include "termbox.h"
#include "args.h"

// argument parsing (args.h)
char *argv0;
struct Options *opts;

int
main ( void )
{
	// initialize termbox
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();
	struct buffer buf;
	
	// initialize drawing
	init(&buf);

	// animate
	while (TRUE)
	{
		// clear the screen
		tb_clear();

		// update framebuffer
		dofire(&buf);

		// draw framebuffer to terminal
		tb_present();
	}

	// cleanup termbox
	tb_shutdown();

	// cleanup framebuffer
	free(buf.tmp_buf);

	return 0;
}
