#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_ONLY_PNG


#include "stb_image.h"
#include "stb_image_write.h"


int main(int argc, char *argv[]) {
	struct timespec t, t1, t2;
	long png=0x0a1a0a0d474e5089;
	char buf[8];
	void *imgfrom, *imgto;
	char *start_image = argv[1];
	int x, y, n;
	FILE *f = fopen(start_image, "r");
	fread(buf, 1, sizeof(long), f); // считываем первые 8 байт, которые отвечают за формат png
	if (*(long *)buf!=png){
		fprintf(stderr, "%s - not correct signature png_file\n", argv[1]);
		return 1;
	}
	imgfrom = stbi_load(argv[1], &x, &y, &n, 0);
	printf("Image was loaded. %d * %d pixels, %d channels\n", x, y, n);
	imgto = malloc(x*y*n);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	work_with_image(imgfrom, imgto, x, y, n);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
	t.tv_sec = t2.tv_sec - t1.tv_sec;
	t.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	if (t.tv_nsec < 0) {
		t.tv_sec--;
		t.tv_nsec += 1000000000;
	}
	printf("C: %ld.%09ld\n", t.tv_sec, t.tv_nsec);
	stbi_write_png(argv[2], x, y, n, imgto, x*n);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	work_with_image_asm(imgfrom, imgto, x, y, n);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
	t.tv_sec = t2.tv_sec - t1.tv_sec;
	t.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	if (t.tv_nsec < 0) {
		t.tv_sec--;
		t.tv_nsec += 1000000000;
	}
	printf("ASM: %ld.%09ld\n", t.tv_sec, t.tv_nsec);
	stbi_write_png(argv[3], x, y, n, imgto, x*n);
	fclose(f);
	return 0;
}
