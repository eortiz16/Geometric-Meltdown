/*
program:	ppm.cpp
author:		Gordon Griesel
date:		Fall 2013
modified:	Erick Ortiz
date:		November 2017

Description:
Read and write PPM files.
   P6 = Packed format (binary)
Files can be used to store images for viewing or texture maps.

format inventor: Jef Poskanzer
When writing, we will follow his suggested limit of 70-character lines.
When reading, we allow for much longer lines.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ppm.h"

Ppmimage *ppm6GetImage(const char *filename)
{
	int i, j, width, height, size, maxval, ntries;
	char ts[4096];
	//unsigned int rgb[3];
	unsigned char c;
	unsigned char *p;
	FILE *fpi;
	Ppmimage *image = (Ppmimage *)malloc(sizeof(Ppmimage));
	if (!image) {
		printf("ERROR: out of memory\n");
		exit(EXIT_FAILURE);
	}

	errno_t filop = fopen_s(&fpi, filename, "r");

	if (!fpi) {
		printf("ERROR: cannot open file **%s** for reading.\n", filename);
		exit(EXIT_FAILURE);
	}
	image->data=NULL;
	char *x = fgets(ts, 4, fpi);
	if (x){}
	if (strncmp(ts, "P6" ,2) != 0) {
		printf("ERROR: File is not ppm RAW format.\n");
		exit(EXIT_FAILURE);
	}
	//comments?
	while (1) {
		c = fgetc(fpi);
		if (c != '#')
			break;
		//read until newline
		ntries=0;
		while (1) {
			//to avoid infinite loop...
			if (++ntries > 10000) {
				printf("ERROR: too many blank lines in **%s**\n", filename);
				exit(EXIT_FAILURE);
			}
			c = fgetc(fpi);
			if (c == '\n')
				break;
		}
	}
	ungetc(c, fpi);
	int r = fscanf_s(fpi, "%u%u%u", &width, &height, &maxval);
	if (r){}
	
	//get past any newline or carrage-return
	ntries=0;
	while (1) {
		//to avoid infinite loop...
		if (++ntries > 10000) {
			printf("ERROR: too many blank lines in **%s**\n", filename);
			exit(EXIT_FAILURE);
		}
		c = fgetc(fpi);
		if (c != 10 && c != 13) {
			ungetc(c, fpi);
			break;
		}
	}
	
	size = width * height * 3;
	image->data = (unsigned char *)malloc(size);
	if (!image->data) {
		printf("ERROR: no memory for image data.\n");
		exit(EXIT_FAILURE);
	}
	image->width = width;
	image->height = height;
	p = (unsigned char *)image->data;
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			*p = fgetc(fpi); p++;
			*p = fgetc(fpi); p++;
			*p = fgetc(fpi); p++;
		}
	}
	fclose(fpi);
	return image;
}

void ppm6CleanupImage(Ppmimage *image)
{
	if (image != NULL) {
		if (image->data != NULL)
			free(image->data);
		free(image);
	}
}

unsigned char *buildAlphaData(Ppmimage *img)
{
	int i;
	int a, b, c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i = 0; i<img->width * img->height * 3; i += 3) {
		a = *(data + 0);
		b = *(data + 1);
		c = *(data + 2);
		*(ptr + 0) = a;
		*(ptr + 1) = b;
		*(ptr + 2) = c;
		*(ptr + 3) = (a | b | c);
		ptr += 4;
		data += 3;
	}
	return newdata;
}