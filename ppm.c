#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

ppm_t* ppm_init(int width, int height, int color){
	int i;
	int j;
	ppm_t* img;

	img = (ppm_t*) malloc(sizeof(ppm_t));
	img->data = (pixel_t*) malloc(sizeof(pixel_t) * width * height);

	img->width = width;
	img->height = height;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			ppm_insert(img, i, j, color);
		}
	}

	return img;
}

void ppm_insert(ppm_t* img, int x, int y, int color){
	int i = x * img->width + y;

	img->data[i].r = color;
	img->data[i].g = color;
	img->data[i].b = color;
}

void ppm_write(ppm_t* img, char* name){
	FILE* archive;
	int i;
	int j;

	archive = fopen(name, "wb");

	fprintf(archive, "P3\n %d %d\n255\n", img->width, img->height);

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			fprintf(archive, "%u %u %u ", img->data[i * img->width + j].r, img->data[i * img->width + j].g, img->data[i * img->width + j].b);
		}
	}

	fclose(archive);
}

void ppm_close(ppm_t* img){
	free(img->data);
	free(img);
}

