#pragma once
class Ppmimage {
public:
	int width;
	int height;
	void *data;
};

extern Ppmimage *ppm6GetImage(const char *filename);
extern void ppm6CleanupImage(Ppmimage *image);
extern unsigned char *buildAlphaData(Ppmimage *img);
