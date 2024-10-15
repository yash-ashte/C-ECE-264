#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "print_integer.h"

int main(int argc, char* argv[]) {
	print_integer(1, 10, "");
	fputc('\n', stdout);
	print_integer(-1, 10, "");
	fputc('\n', stdout);
	print_integer(10, 11, "");
	fputc('\n', stdout);
	print_integer(9, 10, "$");
	fputc('\n', stdout);
	print_integer(-9, 10, "$");
	fputc('\n', stdout);
	print_integer(2, 2, "");
	fputc('\n', stdout);
	print_integer(-2, 2, "");
	fputc('\n', stdout);
	print_integer(26318, 22, "");
	fputc('\n', stdout);
	print_integer(INT_MAX, 36, "@@");
	fputc('\n', stdout);
	print_integer(INT_MIN, 30, "xyz = ");
	fputc('\n', stdout);
  return EXIT_SUCCESS;
}
