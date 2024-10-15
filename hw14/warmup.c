#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void _print_integer(const void* a_value) {
	// TODO: implement
	printf("%d",*(int*)a_value);
}

int _compare_integers(const void* a_first, const void* a_second) {
	return (*(int*)a_first - *(int*)a_second ); // TODO: implement
}

// do not modify the code in main
int main(int argc, char* argv[]) {
	int numbers[5] = {4, 3, 7, 1, 9 };
	void (*print_value_fn)(const void*) = _print_integer;

	qsort(numbers, 5, sizeof(*numbers), _compare_integers);

	for (int i = 0; i < 5; i++) {
		print_value_fn(numbers + i);
		printf(", ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
