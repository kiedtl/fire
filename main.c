#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bool.h"
#include "output.h"
#include "draw.h"
#include "colors.h"
#include "terminfo.h"
#include "termbox.h"
#include "args.h"
#include "ff.h"

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
main(int argc, char *argv[])
{
	opts = (struct Options*) calloc(1, sizeof(struct Options));
	if (opts == NULL) {
		perror("fire: error: calloc()");
	}

	// default args
	opts->animation_speed = 5;
	opts->refresh_rate    = 1;
	size_t output_mode    = TB_OUTPUT_NORMAL;
	opts->truecolor       = FALSE;
	opts->heat_loss       = 45;
	opts->wind            = 1;
	opts->random_wind     = TRUE;
	opts->random_factor   = 4;
	opts->width           = ttywidth();
	opts->height          = ttyheight();

	// argument parsing
	argv0 = argv[0];

	ARGBEGIN {
		case 'F':
			opts->farbfeld_mode = TRUE;
			opts->ff_frame = atoi(ARGF());
			output_mode = TB_OUTPUT_TRUECOLOR;
			opts->truecolor = TRUE;
			break;
		case 'H':
			opts->height = atoi(ARGF());
			break;
		case 'W':
			opts->width = atoi(ARGF());
			break;
		case 't':
			output_mode = TB_OUTPUT_TRUECOLOR;
			opts->truecolor = TRUE;
			break;
		case 's':
			opts->animation_speed = atoi(ARGF());
			break;
		case 'r':
			opts->refresh_rate = atoi(ARGF());
			break;
		case 'l':
			opts->heat_loss = atoi(ARGF());
			break;
		case 'w':
			opts->wind = atoi(ARGF());
			break;
		case 'R':
			opts->random_wind = FALSE;
			break;
		case 'f':
			opts->random_factor = atoi(ARGF());
			break;
		case 'v':
		case 'V':
			printf("%s %s\n", argv0, VERSION);
			return 0;
		case 'h':
		default:
			printf("Usage: %s [-RtVh] [-r rate] [-s speed] [-l loss] [-w wind] [-f fact]\n", argv0);
			printf("Display a nice fiery animation.\n\n");
			printf("ARGUMENTS:\n");
			printf("    -r [rate]    Change refresh rate. (default: 1)\n");
			printf("                 Higher values == slower refresh rate.\n");
			printf("    -s [speed]   Change animation speed. (default: 5)\n");
			printf("                 Higher values == slower animation.\n");
			printf("    -l [loss]    Heat loss for each row upward. (default: 45)\n");
			printf("                 Higher values will lead to a smaller fire.\n");
			printf("    -w [wind]    Wind. Negative values, or values less than one will\n");
			printf("                 cause the fire to be blown west. (default: 1)\n");
			printf("                 To disable wind, set this value to 0 and use the -R flag.\n");
			printf("    -f [fact]    Set the chance of the random value being refreshed\n");
			printf("                 for each tile in the fire animation. (default: 4)\n");
			printf("                 High values will cause a matrix-like effect.\n");
			printf("    -R           Disable random wind factor.\n");
			printf("    -t           Enable truecolor. (Will not work on *rxvt)\n");
			printf("    -h           Display this help message and exit.\n");
			printf("    -V           Display version and exit.\n\n");
			printf("EXAMPLES:\n");
			printf("    %s                    'Normal' fire.\n", argv0);
			printf("    %s -R -w0 -f100       Cmatrix-esque effect.\n", argv0);
			printf("    %s -l2 -w2            Small fire with wind blowing east.\n", argv0);
			printf("    %s -R -w0 -f1000000   Heatwaves!\n", argv0);
			printf("    %s -t -l2 -f3         Truecolor fire animation.\n\n", argv0);
			printf("(c) Kiëd Llaentenn, nullgemm\n");
			printf("https://github.com/lptstr/fire\n");

			return 0;
	} ARGEND

	// initialize termbox
	tb_init(); /* check return value */
	tb_select_output_mode(output_mode);
	tb_clear();

	struct buffer buf;
	struct tb_event e;
	
	// initialize drawing
	init(&buf, opts->width, opts->height);

	uint64_t ctr = 0;

	// animate
	while (TRUE) {
		ctr += 1;

		// update framebuffer
		dofire(&buf);

		/* check if we should print the image now */
		if (opts->farbfeld_mode && ctr >= opts->ff_frame) {
			tb_shutdown(); /* shutdown so we can output the image to stdout */

			if (isatty(STDOUT_FILENO)) {
				EPRINT("fire: cowardly refusing to write farbfeld image to the terminal.\n");
				return 1;
			}

			ff_from_tbscr(opts->width, opts->height, buf.buf,
				(struct tb_cell*) &truecolors, stdout);

			cleanup(&buf);
			return 0;
		}

		/* don't display or check for events if not on refresh frame */
		if ((ctr % opts->refresh_rate) != 0 || opts->farbfeld_mode) {
			continue;
		}

		// draw framebuffer to terminal
		tb_present();

		// event handling
		int err = (size_t) tb_peek_event(&e, opts->animation_speed);

		if (err < 0) {
			continue;
		}

		// handle keypresses
		//     q, ctrl+c, ctrl+d => quit
		/* TODO: handle resizes */
		if (e.type == TB_EVENT_KEY) {
			switch (e.ch) {
			case 'q':
				goto cleanup;
			default:
				break;
			}

			switch (e.key) {
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
	tb_shutdown();
	return 0;
}
