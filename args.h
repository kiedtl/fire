//
// Copy me if you can.
// by 20h
//

// This file was proudly stol^Hborrowed
// from the st project.
//
// (c) all st contributors. View the LICENSE at:
// https://git.suckless.org/st/file/LICENSE.html


#ifndef ARGS_INCLUDED
#define ARGS_INCLUDED
#include "bool.h"
#include "args.h"

#ifdef __OpenBSD__
#include "sys/types.h"
#else
#include "stdint.h"
#endif

extern char *argv0;

typedef struct Options {
	size_t refresh_rate;
	size_t animation_speed;
	size_t heat_loss;
	size_t wind;
	size_t random_factor;
	bool random_wind;
	bool truecolor;

	uint32_t width;
	uint32_t height;

	bool farbfeld_mode;
	size_t ff_frame;
} Options;

/* use main(int argc, char *argv[]) */
#define ARGBEGIN	for (argv0 = *argv, argv++, argc--;\
					argv[0] && argv[0][0] == '-'\
					&& argv[0][1];\
					argc--, argv++) {\
				char argc_;\
				char **argv_;\
				int brk_;\
				if (argv[0][1] == '-' && argv[0][2] == '\0') {\
					argv++;\
					argc--;\
					break;\
				}\
				int i_;\
				for (i_ = 1, brk_ = 0, argv_ = argv;\
						argv[0][i_] && !brk_;\
						i_++) {\
					if (argv_ != argv)\
						break;\
					argc_ = argv[0][i_];\
					switch (argc_)

#define ARGEND			}\
			}

#define ARGC()		argc_

#define EARGF(x)	((argv[0][i_+1] == '\0' && argv[1] == NULL)?\
				((x), abort(), (char *)0) :\
				(brk_ = 1, (argv[0][i_+1] != '\0')?\
					(&argv[0][i_+1]) :\
					(argc--, argv++, argv[0])))

#define ARGF()		((argv[0][i_+1] == '\0' && argv[1] == NULL)?\
				(char *)0 :\
				(brk_ = 1, (argv[0][i_+1] != '\0')?\
					(&argv[0][i_+1]) :\
					(argc--, argv++, argv[0])))

#endif
