#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "smintf.h"

int _count_strlen(const char *str) {
int length = 0;
for(int i=0; str[i]!='\0'; i++)
    {
        length++; //Counting the length.
    }
return length;

}

char* smintf(const char *format, ...){
	va_list more_args;
	va_start(more_args,format);
	
//	int length = 0;
	char char_arg;
	char *str_arg;
	int strlen = _count_strlen(format);
/*	for (int i = 0; i < strlen; i++) {
		if (format[i] == '%') {
			if (i + 1 == strlen) {
				length++;
			}
			else {
				switch(format[i + 1]) {
					case 'c': {
						char_arg = va_arg(more_args, int);
						length++;
						break;
					} 	
					case 's': {
						str_arg = va_arg(more_args, char*);
						length += _count_strlen(str_arg);
						break;
					}	
					case '%': {
						length++;
						break;
					}
					default: {
						length++;
					} 
				}					
			}	

			
		}
	} */
	char* cop = (char*) malloc(sizeof(char) * 500);
	int count = 0;
	if (cop != NULL) {
	
	for (int i = 0; i <= strlen; i++) {
		if (format[i] == '%') {
			switch(format[i + 1]) {
				case 'c': {

						char_arg = va_arg(more_args, int);
					cop[count] = char_arg;
					i = i + 1;
					count++;
					break;
				} 
				case 's': {

						str_arg = va_arg(more_args, char*);
					for (int j = 0; str_arg[j] != '\0'; j++) {
						cop[count] = str_arg[j];
						count++;
					}
					i = i + 1;
					break;
				}
				case 'd': {
					int int_arg = va_arg(more_args, int);
					unsigned int num;
					if (int_arg < 0) {
						cop[count] = '-';
						count++;
						num = -int_arg;
					}
					else {
						num = int_arg;
					}
					int digit;
					int divisor = 1;
					while (divisor <= (num / 10)) {
						divisor = divisor * 10;
					}
					while (divisor > 0) {
        				digit = num / divisor;
        				num = num % divisor;
        				divisor = divisor / 10;
        			  	cop[count] = '0' + digit;
						count++;
					}
					i = i + 1;
					break;
				}
				case 'x': {
					int int_arg = va_arg(more_args, int);
					unsigned int num;
					if (int_arg < 0) {
						cop[count] = '-';
						count++;
						num = -int_arg;
					}
					else {
						num = int_arg;
					}
					cop[count] = '0';
					count++;
					cop[count] = 'x';
					count++;
					int digit = 0;
					int divisor = 1;
					while (divisor <= (num / 16)) {
						divisor = divisor * 16;
					}
					while (divisor > 0) {
        				digit = num / divisor;
        				num = num % divisor;
        				divisor = divisor / 16;
        				if (digit < 10) {
				        	cop[count] = '0' + digit;
							count++;
				        }
				        else {
							cop[count] = 'a' + digit - 10;
							count++;
	   					}
					}
					i = i + 1;
					break;
				}
				case 'b': {
					int int_arg = va_arg(more_args, int);
					unsigned int num;
					if (int_arg < 0) {
						cop[count] = '-';
						count++;
						num = -int_arg;
					}
					else {
						num = int_arg;
					}
					cop[count] = '0';
					count++;
					cop[count] = 'b';
					count++;
					int digit = 0;
					int divisor = 1;
					while (divisor <= (num / 2)) {
						divisor = divisor * 2;
					}
					while (divisor > 0) {
        				digit = num / divisor;
        				num = num % divisor;
        				divisor = divisor / 2;
        				cop[count] = '0' + digit;
						count++;
					}
					i = i + 1;
					break; 
				}
				case '$': {
					int int_arg = va_arg(more_args, int);
					unsigned int num;
					unsigned int check;
    				if (int_arg < 0) {
				        cop[count] = '-';
						count++;
				    	num = -int_arg;
						check = -int_arg;
    				}
				    else {
					    num = int_arg;
						check = int_arg;
    				}
					cop[count] = '$';
					count++;
					int divisor = 1;
    				while (divisor <= num / 10) {
					    divisor = divisor * 10;
    				}
					if ((num % 10) == num ) {
						cop[count] = '0';
						count++;
						cop[count] = '.';
						count++;
						cop[count] = '0';
						count++;
					}
				    int digit;
				    while (divisor > 0) {
				        digit = num / divisor;
        				num = num % divisor;
						if (divisor == 10) {
							if (check < 100) {
								cop[count] = '0';
								count++;
							}
							cop[count] = '.';
							count++;
						}
        				divisor = divisor / 10;
				        cop[count] = '0' + digit;
						count++;
					}
					i = i + 1;
					break;
				}
				case '%': {
					cop[count] = '%';
					i = i + 1;
					count++;
					break;
				}
				default: {
					cop[count] = format[i];
					count++;
				} 
			}
		}
		else {
			cop[count] = format[i];
			count++;
		}
	}

cop[count] = '\0';
	}
va_end(more_args);
return cop;

}
