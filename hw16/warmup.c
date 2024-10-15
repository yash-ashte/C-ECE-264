#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct { 
	int x;
	int y;
 } Point;

char* read_file(const char* path, const char** a_error) {
	FILE* fp;
	fp = fopen(path, "r");
	//error handle file not found
	if (fp == NULL) {
		if (*a_error == NULL) {
			*a_error = "read_file() failed because fp == NULL";
		}
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int s = length + 1;
	char* content = (char*)malloc(s);
	if (content == NULL) {
		if (*a_error == NULL) {
			*a_error = "read_file() failed because malloc mailed";
		}
		return NULL;
	}
	int i = fread(content, 1, length, fp);

	if (i != length) {
		if (*a_error == NULL) {
			*a_error = "read_file() failed because file didn't read completely";
		}
		return NULL;

	}
	content[length] = '\0';
	fclose(fp);
	return content;
}

void write_file(const  char* path, const char* contents, const char** a_error) {
	FILE* fp;
	fp = fopen(path, "w");
	//error handle file not found
	if (fp == NULL) {
		if (*a_error == NULL) {
			*a_error = "write_file() failed because fp == NULL";
		}
		return;
	}
	int len = strlen(contents);
	int i = fwrite(contents, sizeof(char), len, fp);
	if (i != len) {
		if (*a_error == NULL) {
			*a_error = "write_file() failed because file didn't writee completely";
		}
		return;
	}
	fclose(fp);
}

Point read_point(const char* path, const char** a_error) {
	FILE* fp;
	Point p;
	fp = fopen(path, "rb");
	//fseek(fp, 0, SEEK_END);
	//int length = ftell(fp);
	//fseek(fp, 0, SEEK_SET);
	//int num = length/sizeof(Point);
	fread(&p, sizeof(Point), 1, fp);
	fclose(fp);
	return p;
}

void write_point(const char* path, Point p, const char** a_error) {
	FILE* fp;
	fp = fopen(path, "wb");
	fwrite(&p, sizeof(Point), 1, fp);
	fclose(fp);
}




int main(int argc, char* argv[]) {
	const char* err = NULL;
	write_file("input.txt", "I probably made the right choice", &err);

	char* str = read_file("input.txt", &err);
	if (str == NULL) {
		fprintf(stderr, err);
		assert(err != NULL);
		return EXIT_FAILURE;
	}
	else {
		assert(err == NULL);
		printf("%s\n", str);
	}
	free(str);

	Point p = {69, 420};
	Point q;
	write_point("input.txt", p, &err);
	q = read_point("input.txt", &err);
	printf("%d\n", q.x);
	printf("%d\n", q.y);

	return EXIT_SUCCESS;
}


