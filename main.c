#include <stdlib.h>

#include "bool.h"
#include "output.h"
#include "draw.h"
#include "termbox.h"
#include "args.h"

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "stdint.h"
#endif

#define VERSION "0.2.0"

// argument parsing (args.h)
char *argv0;
struct Options *opts;

int
main ( int argc, char *argv[] )
{
	opts = (struct Options*) calloc(1, sizeof(struct Options*));
	if (opts == NULL) {
		EPRINT("fire: error: cannot ");
		perror("calloc()");
	}

	// default args
	opts->refresh_rate  = 5;
	opts->truecolor     = FALSE;
	size_t output_mode  = TB_OUTPUT_NORMAL;

	// argument parsing
	argv0 = argv[0];

	ARGBEGIN {
		case 't':
			output_mode = TB_OUTPUT_TRUECOLOR;
			opts->truecolor = TRUE;
			break;
		case 'r':
			opts->refresh_rate = atoi(ARGF());
			break;
		case 'V':
			printf("%s %s\n", argv0, VERSION);
			exit(EXIT_SUCCESS);
		case 'h':
		default:
			printf("Usage: %s [-tVh] [-r rate]\n", argv0);
			printf("Display a nice fiery animation.\n\n");
			printf("ARGUMENTS:\n");
			printf("    -r [rate]   Change refresh rate. (default: 5)\n");
			printf("    -t          Enable truecolor. (Will not work on *rxvt)\n");
			printf("    -h          Display this help message and exit.\n");
			printf("    -V          Display version and exit.\n\n");
			printf("(c) Kiëd Llaentenn, nullgemm\n");
			printf("https://github.com/lptstr/fire\n");

			exit(EXIT_SUCCESS);
	} ARGEND

	// initialize termbox
	tb_init();
	tb_select_output_mode(output_mode);
	tb_clear();
	struct buffer buf;
	struct tb_event e;
	
	// initialize drawing
	init(&buf);

	// animate
	while (TRUE)
	{
		// clear the screen
		//tb_clear();

		// update framebuffer
		dofire(&buf);

		// draw framebuffer to terminal
		tb_present();

		// event handling
		int err = (size_t) tb_peek_event(&e, opts->refresh_rate);

		if (err < 0)
			continue;

		if (e.type == TB_EVENT_KEY)
		{
			switch (e.ch) {
			case 'q':
				goto cleanup;
			default:
				break;
			}

			switch (e.key)
			{
				case TB_KEY_CTRL_C:
				case TB_KEY_CTRL_D:
					goto cleanup;
				default:
					break;
			}
		}
	}

cleanup:
	cleanup(&buf);
	return 0;
}
