#include <stdlib.h>

#include "bool.h"
#include "output.h"
#include "draw.h"
#include "types.h"
#include "termbox.h"
#include "args.h"

#define VERSION	"0.1.0"

// argument parsing (args.h)
char *argv0;
struct Options *opts;

int
main ( int argc, char *argv[] )
{
	// argument parsing
	argv0 = argv[0];

	ARGBEGIN {
		case 'V':
			PRINT("%s %s\n", argv0, VERSION);
			exit(0);
		case 'h':
		default:
			PRINT("fire %s\n(c) Kied Llaentenn and contributors\n", VERSION);
			PRINT("https://github.com/lptstr/fire\n");
			PRINT("\nUSAGE:\n\t$ fire\n\n");
			PRINT("OPTIONS:\n\t-V\tshow version and exit.\n");
			PRINT("\t-h\tshow this help message and exit.\n\n");
			exit(1);
	} ARGEND

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
	free(buf.buf);

	return 0;
}
