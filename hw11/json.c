#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "clog.h"
#include "json.h"

bool parse_int(int* a_value, char const** a_pos) {
/*    if (a_value == NULL || a_pos == NULL || *a_pos == NULL) {
        return false;  // Invalid input
    }*/

    const char* pos = *a_pos;
    bool negative = false;

    if (*pos == '-') {
        negative = true;
        pos++;
 
    }

    int result = 0;
    bool valid = true;
	bool ch = false;

    while (valid) {
		if (*pos >= '0' && *pos <= '9') {

			valid = true;
        	result = (result * 10) + (*pos - '0');

        	pos++;
			ch = true;

		}
		else {
				
			valid = false;
		}
		//pos = pos + 1;
    }


    if (ch) {
		

        *a_value = negative ? -result : result;
        *a_pos = pos;

        return true;
    } else {
		*a_pos = pos;	

        return false;
    }
}


bool parse_string(char** a_string, const char** a_pos) {
    (*a_pos)++;


    const char* end_pos = *a_pos;
    while (*end_pos != '"' && *end_pos != '\0' && *end_pos != '\n') {
        end_pos++;
    }
   if (*end_pos != '"') {

		*a_pos = end_pos;

       return false;
	}

    size_t length = end_pos - *a_pos;

    *a_string = (char*)malloc((length + 1) * sizeof(char));
    assert(*a_string != NULL);
    for (size_t i = 0; i < length; i++) {
        (*a_string)[i] = (*a_pos)[i];
    }
    (*a_string)[length] = '\0';

    *a_pos = end_pos + 1;
    return true;
}




bool parse_element(Element* a_element, char const** a_pos) {

	
	while (isspace(**a_pos))	{
		(*a_pos) = (*a_pos) + 1;
		
	}
	

	if ((isdigit(**a_pos)) || (**a_pos == '-')) {
		a_element->type = ELEMENT_INT;


		return parse_int(&(a_element->as_int), a_pos);
		
	}
	else if (**a_pos == '"') {
		a_element->type = ELEMENT_STRING;
		return parse_string(&(a_element->as_string), a_pos);
	}
	else {
		return false;
	}
}


void print_element(Element element) {
    switch (element.type) {
        case ELEMENT_INT:
            printf("%d", element.as_int);
            break;
		default:
            printf("\"%s\"", element.as_string);
            break;
    }
}

void free_element(Element element) {
    switch (element.type) {
        case ELEMENT_STRING:
            free(element.as_string);
            break;
/*        case ELEMENT_LIST: {
           LinkedListNode* current = element.data.linked_list;
            while (current != NULL) {
                LinkedListNode* next = current->next;
                free(current);
                current = next;
            }
            break;
        }*/
        default:
 
            break;
    }
}

