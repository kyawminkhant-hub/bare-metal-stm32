#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>
#include <stdio.h>

#define PINMUX(PORT, PIN, AF)           (((PORT) << 8) | ((PIN) << 0) | ((AF) << 16))
#define PIN(PINMUX)                     ((PINMUX) & 0xFF)
#define PORT(PINMUX)                    (((PINMUX) >> 8) & 0xFF)
#define AF(PINMUX)                      (((PINMUX) >> 16) & 0xFF)

#define PINMAP(port, pin)               port, pin

#define BIT(pos)			            (1U << pos)

#endif /* _UTIL_H_ */

