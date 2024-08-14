#ifndef MATH_NERD_KMP_H
#define MATH_NERD_KMP_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

void generate_failure_table(char const *, int, int64_t *);

array_t *knuth_morris_pratt(char *, char *);

#endif // MATH_NERD_KMP_H