

void work_with_image(void *from, void *to, int x, int y, int n) {
	char * src = from;
	char * dst = to;
	int indexFrom, indexTo;
	char tmp[4];
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x / 2 + 1; j++) {
			indexFrom = i * x + j;
			indexTo = (i + 1) * x - 1 - j;
			if (indexFrom > indexTo) break;
			//if (indexFrom < 10) {
			//	printf("x=%d, y=%d, xTo=%d, yTo=%d, indexFrom=%d, indexTo=%d, n=%d\n", j, i, x - j, i, indexFrom * n, n *  indexTo, n);
			//}

			//printf("x=%d, y=%d, xTo=%d, yTo=%d, indexFrom=%d, indexTo=%d, n=%d\n", j, i, x - j, i, indexFrom * 4,4 *  indexTo);

			for (int h = 0; h < n; h++) {
				dst[indexFrom*n+h] = src[indexTo*n+h];
				dst[indexTo*n+h] = src[indexFrom*n+h];
			}
//			dst[indexFrom*4] = src[indexTo*4];
//			dst[indexFrom*4+1] = src[indexTo*4+1];
//			dst[indexFrom*4+2] = src[indexTo*4+2];
//			dst[indexFrom*4+3] = src[indexTo*4+3];
//			dst[indexTo*4] = src[indexFrom*4];
//		 	dst[indexTo*4+1] = src[indexFrom*4+1];
//			dst[indexTo*4+2] = src[indexFrom*4+2];
//			dst[indexTo*4+3] = src[indexFrom*4+3];
		} 
	}
	return;
}


