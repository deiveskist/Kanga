#ifndef _PPM_H_
#define _PPM_H_

#define WHITE 0
#define BLACK 1

typedef struct{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} pixel_t;

typedef struct {
	short width;
	short height;
	pixel_t* data;
} ppm_t;

ppm_t* ppm_init(int, int, int);
void ppm_insert(ppm_t*, int, int, int);
void ppm_write(ppm_t*, char* name);
void ppm_close(ppm_t*);

#endif // _PPM_H_
