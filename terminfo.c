/*
 * terminfo.c: get TTY/console's buffer
 * height and width.
 *
 * TODO: test this on Windows 10.
 *
 * why is all Windows programming so
 * damn complicated.
 *
 * Thanks to this SO question for Windows stuff:
 * stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
 *
 * (c) Kiëd Llaentenn and contributors
 * See the LICENSE.md file for copyright
 * information.
 */

#include <stdio.h>
#include <stdint.h>

#include "terminfo.h"

#if defined(_WIN32) || defined(__WIN32__)
#define WOE_IS_ME
#endif

#ifdef WOE_IS_ME
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

/*
 * sizes to fall back to if:
 *     1) stdout isn't a tty
 *     2) if on Windows (temporary, only until win32
 *     support it added
 */
const uint16_t fallback_width  = 80;
const uint16_t fallback_height = 24;

/* file descriptor to get dimensions of */
#ifdef WOE_IS_ME
CONST DWORD fd = STD_OUTPUT_HANDLE;
#else
const size_t fd = STDOUT_FILENO;
#endif

uint16_t
ttywidth(void)
{
#ifdef WOE_IS_ME
	/* why on earth does _isatty return NONZERO
	 * if FD is a tty?! */
	if (_isatty(fd))
		return fallback_width;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(
		GetStdHandle(fd), &csbi
	);
	
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
	if (!isatty(fd))
		return fallback_width;

	struct winsize w;
	ioctl(fd, TIOCGWINSZ, &w);
	return w.ws_col;
#endif
}

uint16_t
ttyheight(void)
{
#ifdef WOE_IS_ME
	if (_isatty(fd))
		return fallback_height;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(
		GetStdHandle(fd), &csbi
	);

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	if (!isatty(fd))
		return fallback_height;

	struct winsize w;
	ioctl(fd, TIOCGWINSZ, &w);

	return w.ws_row;
#endif
}
