#ifndef CCURSOR_PORT_H
#define CCURSOR_PORT_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// max integer values for current port
#define _UINT32_MAX UINT32_MAX
#define _INT32_MAX INT32_MAX
#define _INT32_MIN INT32_MIN

#define _UINT16_MAX UINT16_MAX
#define _INT16_MAX INT16_MAX
#define _INT16_MIN INT16_MIN

#define _UINT8_MAX UINT8_MAX
#define _INT8_MAX INT8_MAX
#define _INT8_MIN INT8_MIN

// string parsing functions for current port
#define _strncpy strncpy
#define _strtoul strtoul
#define _strtol strtol
#define _strlen strlen

#endif // CCURSOR_PORT_H
