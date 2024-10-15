#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bmp.h"

bool check_bmp_header(const BMPHeader* bh, FILE* fp) {
	bool cond = true;
	int exp_img = ((bh->width_px *  (bh->bits_per_pixel / 8) + 3) & ~3) * bh->height_px;	
	int exp_file = BMP_HEADER_SIZE + bh->image_size_bytes;
	if (!(bh->type == 0x4d42) || !(bh->offset == BMP_HEADER_SIZE) || !(bh->dib_header_size == DIB_HEADER_SIZE) || (bh->num_planes != 1) || bh->compression != 0 || bh->num_colors != 0 || bh->important_colors != 0 || bh->bits_per_pixel != 24 ||bh->image_size_bytes != exp_img || exp_file != bh->size)	{
		cond = false;
	}
/*	if (!(bh->offset == BMP_HEADER_SIZE)) {
		i = 2;
		cond = false;
	}
	if (!(bh->dib_header_size == DIB_HEADER_SIZE)) {
		i = 3;
		cond = false;
	}
	if (!(bh->num_planes == 1)) {
		i = 4;
		cond = false;
	}
	if (!(bh->compression == 0)) {
		i = 5;
		cond = false;
	}
	if ((bh->num_colors != 0) || (bh->important_colors != 0)) {
		i = 6;
		cond = false;
	}
	if (!(bh->bits_per_pixel == 24)) {
		i = 7;
		cond = false;
	}
	int cur = ftell(fp);
	printf("%d  %d  %d\n", bh->width_px, bh->height_px, bh->bits_per_pixel);
	printf("img = %d\n", bh->image_size_bytes);
	int exp_img = ((bh->width_px *  (bh->bits_per_pixel / 8) + 3) & ~3) * bh->height_px;

	if (bh->image_size_bytes != exp_img) {
		i = 7;
		cond = false;
	}
	fseek(fp, 0, SEEK_END);
	//int len = ftell(fp);
	fseek(fp, cur, SEEK_SET);
	int exp_file = BMP_HEADER_SIZE + bh->image_size_bytes;
	
	if (exp_file != bh->size) {
		i = 8;
		cond = false;
	}

	printf("%d\n", i);*/
	
	return cond;
}

BMPImage* read_bmp(FILE* fp, const char** a_error) {
	//printf("in\n");
	BMPHeader bh;
	int i = fread(&bh, sizeof(BMPHeader), 1, fp);
	//printf("read1\n");

	*a_error = (i == 1 ? NULL : strerror(errno));
	if (!check_bmp_header(&bh, fp)) {
        if (*a_error == NULL) {
			//printf("error ho gaya\n");
			*a_error = "Invalid BMP Image Header";
		}
        return NULL;
    }
//	printf("before read2\n");
	BMPImage* img = malloc(sizeof(*img));
	*a_error = (img != NULL ? NULL : strerror(errno));
//	printf("after malloc\n");
	img->header = bh;
	img->data = malloc(sizeof(char) * bh.image_size_bytes);
	*a_error = (img->data != NULL ? NULL : strerror(errno));
	i =	fread(img->data, bh.image_size_bytes, 1, fp);
//	printf("after read2\n");
	*a_error = (i == 1 ? NULL : strerror(errno));
//	printf("all should work\n");
	return img;
}

bool write_bmp(FILE* fp, BMPImage* image, const char** a_error) {
	if (image == NULL || image->data == NULL) {
		*a_error = "Invalid BMPImage";
		return false;
	}
	int i = fwrite(&image->header, sizeof(BMPHeader), 1, fp);
	*a_error = (i == 1 ? NULL : strerror(errno));

	int j = fwrite(image->data, image->header.image_size_bytes, 1, fp);
		
	*a_error = (j == 1 ? NULL : strerror(errno));
	return true;
}


void free_bmp(BMPImage* img) {
	if (img != NULL) {
		if (img->data != NULL) {
			free(img->data);
		}
		free(img);
	}
}

BMPImage* crop_bmp(const BMPImage* image, int x, int y, int w, int h, const char** a_error) {
	if (image == NULL || image->data == NULL) {
		*a_error = "img is null";
		return NULL;
	}
	int start = BMP_HEADER_SIZE + (y * image->header.width_px + x) * (image->header.bits_per_pixel / 8);
	int crop_size = w * h * (image->header.bits_per_pixel / 8);
	BMPImage* crop_img = malloc(sizeof(*crop_img));
	*a_error = (crop_img != NULL ? NULL : strerror(errno));
	crop_img->data = malloc(sizeof(char) * crop_size);
	*a_error = (crop_img->data != NULL ? NULL : strerror(errno));
	crop_img->header = image->header;
	crop_img->header.width_px = w;
	crop_img->header.height_px = h;
	crop_img->header.image_size_bytes = crop_size;
	crop_img->header.size = BMP_HEADER_SIZE + crop_size;
	crop_img->header.offset = BMP_HEADER_SIZE;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int soff = start + (i * image->header.width_px + j) * (image->header.bits_per_pixel / 8);
			int doff = (i * w + j) * (image->header.bits_per_pixel / 8);
			for (int k = 0; k < (image->header.bits_per_pixel / 8); k++) {
				crop_img->data[doff + k] = image->data[soff + k];
			}
		}
	}

	return crop_img;
}
