#include <stdio.h>
#include <stdlib.h>

#ifndef IMAGE
#define IMAGE

void work_image_c(void *, void *, int, int);

void work_image_asm(void *, void *, int, int);

void work_image_asmSSE(void *, void *, int, int);

#endif
