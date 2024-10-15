#include <stdio.h>
#include <stdbool.h>
#include "clog.h"
#include "json.h"

bool parse_int(int* a_value, char const** a_pos) {
    /*if (a_value == NULL || a_pos == NULL || *a_pos == NULL) {
        return false;  // Invalid input
    }*/

    const char* pos = *a_pos;
    bool negative = false;

	int c = 0;
    // Check for negative sign
    if (*pos == '-') {
        negative = true;
        pos++;
		c++;
    }

    int result = 0;
    bool valid = true;
	bool ch = false;
    // Parse digits
    while (valid) {
		if (*pos >= '0' && *pos <= '9') {
        	c++;
			valid = true;
        	result = (result * 10) + (*pos - '0');
	//		printf("while");
        	pos++;
			ch = true;
		}
		else {

			//ch = true;
			valid = false;
		}
    }

    // Store the parsed value
    if (ch) {
		
		//printf("if");
        *a_value = negative ? -result : result;
        *a_pos = pos - c + 1;
	//	printf("a- %p\n", *a_pos);
        return true;
    } else {
        return false;
    }
}

