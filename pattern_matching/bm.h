#ifndef MATH_NERD_BM_H
#define MATH_NERD_BM_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

void generate_last_occurrence_table(char const *const, int, int64_t[]);

array_t *boyer_moore(char *, char *);

#endif // MATH_NERD_BM_H