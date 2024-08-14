#ifndef MATH_NERD_RK_H
#define MATH_NERD_RK_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

uint64_t simple_hash(char *, int, int);

array_t *rabin_karp(char *, char *);

#endif // MATH_NERD_RK_H