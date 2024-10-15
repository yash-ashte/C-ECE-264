#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "mintf.h"

void mintf(const char *format, ...){
	va_list more_args;
	va_start(more_args,format);
	for (int i = 0; format[i] != '\0'; i++) {
//  	fputc(format[i], stdout);
		if (format[i] == '%') {
			int next = i + 1;
			switch(format[next]) {
				case '\0': {
					fputc('%', stdout);
					break;
				}
				case 'c': {
					char char_arg = va_arg(more_args, int);
					fputc(char_arg, stdout);
					i = i + 1;
					break;
				}
				case 's': {
					char *str_arg = va_arg(more_args, char *);
					fputs(str_arg, stdout);
					i = i + 1;
					break;
				}
				case 'd': {
					int int_arg = va_arg(more_args, int);
					print_integer(int_arg, 10, "");
					i = i + 1;
					break;
				}
				case 'x': {
					int int_arg = va_arg(more_args, int);
					print_integer(int_arg, 16, "0x");
					i = i + 1;
					break;
				}
				case 'b': {
					int int_arg = va_arg(more_args, int);
					print_integer(int_arg, 2, "0b");
					i = i + 1;
					break; 
				}
				case '$': {
					int int_arg = va_arg(more_args, int);
					unsigned int num;
    				if (int_arg < 0) {
				        fputc('-', stdout);
				    	num = -int_arg;
    				}
				    else {
					    num = int_arg;
    				}
					fputc('$', stdout);
					int divisor = 1;
    				while (divisor <= num / 10) {
					    divisor = divisor * 10;
    				}
					if (num == 0) {
						fputc('0', stdout);
						fputc('.', stdout);
						fputc('0', stdout);
						//fputc('0', stdout);
					}
				    int digit;
				    while (divisor > 0) {
				        digit = num / divisor;
        				num = num % divisor;
						if (divisor == 10) {
							fputc('.', stdout);
						}
        				divisor = divisor / 10;
				        if (digit < 10) {
        					fputc('0' + digit, stdout);
        				}
        				else {
							fputc('a' + digit - 10, stdout);
    					}
					}
					i = i + 1;
					break;
				}
				case '%': {
					fputc('%', stdout);
					i = i + 1;
					break;
				}
				default:
					fputc(format[i], stdout);
			}
		}
		else {
			fputc(format[i], stdout);
		}
}

va_end(more_args);
}

void print_integer(int n, int radix, char* prefix){
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
}
