/*
 * terminfo.h: get TTY/console's buffer
 * height and width.
 *
 * (c) Kiëd Llaentenn and contributors
 * See the LICENSE.md file for copyright
 * information.
 */

#ifndef TERMINFO_H
#define TERMINFO_H

#include <stdint.h>

uint16_t ttywidth(void);
uint16_t ttyheight(void);

#endif
