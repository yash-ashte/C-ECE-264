#include <stdio.h>
#include <stdlib.h>
#include "count_words.h"

int main(int argc, char* argv[]) {
	printf("%u\n", count_words("My apples are sweet."));               // should print 4
	printf("%u\n", count_words("My friend's apples are sweeter."));    // should print 5
	printf("%u\n", count_words("A pear is sweeter than an apple.."));  // should print 7

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
