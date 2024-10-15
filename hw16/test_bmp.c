#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bmp.h"
#include "miniunit.h"

static int _test_6x6() {
	mu_start();
	FILE* fp;
	fp = fopen("6x6_24bit.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	fclose(fp);
	fp = NULL;
	mu_check(err == NULL);
	mu_check(img != NULL);
	printf("test works\n");
	printf("%d\n", img->header.type);
	fp = fopen("write.txt", "wb");
	bool res = write_bmp(fp, img, &err);
	mu_check(res == true);
	mu_check(err == NULL);
//free_bmp(img);
	BMPImage* new;
	new = crop_bmp(img, 0, 0, 4, 4, &err);
	mu_check(new->header.height_px == 4);
	
	free_bmp(img);
	free_bmp(new);
	mu_end();
}

static int _test_c_plane() {
	mu_start();
	FILE* fp;
	fp = fopen("corrupt_airplanei.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
 fprintf(stderr, err);
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	fclose(fp);
	fp = NULL;
	mu_end();
}

static int _test_car() {
	mu_start();
	FILE* fp;
	fp = fopen("car.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	fclose(fp);
	fp = NULL;
	mu_check(err == NULL);
	mu_check(img != NULL);
	printf("test works\n");
	printf("%d\n", img->header.type);
	fp = fopen("write.txt", "wb");
	bool res = write_bmp(fp, img, &err);
	mu_check(res == true);
	mu_check(err == NULL);
//	free_bmp(img);
	BMPImage* new;
	new = crop_bmp(img, 0, 0, 4, 4, &err);
	mu_check(new->header.height_px == 4);
	free_bmp(img);
	free_bmp(new);
	mu_end();
}


static int _test_c_car() {
	mu_start();
	FILE* fp;
	fp = fopen("corrupt_carw.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
 fprintf(stderr, err);
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	fclose(fp);
	fp = NULL;
	mu_end();
}

static int _test_c_earth() {
	mu_start();
	FILE* fp;
	fp = fopen("corrupt_green_earthh.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
 fprintf(stderr, err);
 fclose(fp);
 fp = NULL;
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	mu_end();
}

static int _test_c_train() {
	mu_start();
	FILE* fp;
	fp = fopen("corrupt_purduetraini.bmp", "rb");
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
 fprintf(stderr, err);
 fclose(fp);
 fp = NULL;
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	mu_end();
}

static int _test_c_trainw() {
	mu_start();
	FILE* fp;
	fp = fopen("corrupt_purduetrainw.bmp", "rb");
	assert(fp != NULL);
	BMPImage* img;
	const char* err = NULL;
	img = read_bmp(fp, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
 fprintf(stderr, err);
 fclose(fp);
 fp = NULL;
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	mu_end();
}


static int _test_null() {
	mu_start();
	FILE* fp;
//	fp = fopen("corrupt_carw.bmp", "rb");
	BMPImage* img = NULL;
	const char* err = NULL;
//	img = read_bmp(fp, &err);
	fp = fopen("write.txt", "wb");
	write_bmp(fp, img, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);

	fclose(fp);
	fp = NULL;
	printf("%s\n", err);
 	fprintf(stderr, err);
	err = NULL;
	img = crop_bmp(img, 0, 0, 4,4, &err);
	mu_check(err != NULL);
	mu_check(img == NULL);
	
 	fprintf(stderr, err);
//	printf("test works\n");
//	printf("%d\n", img->header.type);
	free_bmp(img);
	mu_end();
}





int main(int argc, char* argv[]) {

	mu_run(_test_c_earth);
	mu_run(_test_6x6);
	mu_run(_test_car);
	mu_run(_test_c_plane);
	mu_run(_test_c_car);
	mu_run(_test_null);
	//mu_run(_test_c_earth);
	mu_run(_test_c_train);
	mu_run(_test_c_trainw);
}
