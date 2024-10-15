#include <stdio.h>
#include <assert.h>
#include "print_integer.h"



void print_integer(int n, int radix, char* prefix ) {
	assert((radix > 1) && (radix < 37));
	unsigned int num;	
	if (n < 0) {
		fputc('-', stdout);
		num = -n;
	}
	else {
		num = n;
	}
	for(int i = 0; prefix[i] != '\0'; i++) {
		fputc(prefix[i], stdout);
	}
	if (n == 0) {
		fputc('0', stdout);
		return;
	}

	int divisor = 1;
	while (divisor <= num / radix) {
		divisor = divisor * radix;
	}

	int digit;
	while (divisor > 0) {
		digit = num / divisor;
		num = num % divisor;
		divisor = divisor / radix;
		if (digit < 10) {
			fputc('0' + digit, stdout);
		}
		else {
			fputc('a' + digit - 10, stdout);

		}
	}
/*	char buff[65];
	int index = 0;
	while (num != 0) {
		int rem = num % radix;
		if (rem < 10) {
	  		buff[index] = '0' + rem;
		}
		else {
			buff[index] = 'a' + rem - 10;
		}
		num = num / radix;
		index++;
	}
	for (int i = index - 1; i >= 0; i--) {
		fputc(buff[i], stdout);
	}*/
}
