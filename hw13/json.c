#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "clog.h"
#include "json.h"


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Helper function to free the linked list
void _free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free_element(temp->element);
		free(temp);
    }
}

bool parse_list(Node** a_head, const char** a_pos) {
    /*if (a_head == NULL || a_pos == NULL || *a_pos == NULL) {
        return false; // Invalid input arguments
    }*/
	printf("in");
    const char* pos = *a_pos;

    // Eat whitespace
    while (isspace(*pos)) {
        pos++;
    }

    // Check for the start of the list '['
    if (*pos != '[') {
        return false;
    }
    pos++; // Move to the next character after '['

    // Create the head of the linked list
    *a_head = NULL;
 if (*pos == ']') {
        pos++; // Move to the next character after ']'
		//printf("%p\n", pos);
		*a_pos = pos;
        return true; // Successfully parsed the list
    }
    // Keep track of the previous node to link elements in the linked list
    Node* prevNode = NULL;

    // Parse elements in the list (if any)
    while (*pos != '\0') {
        Element element;

        // Parse the current element
        if (!parse_element(&element, &pos)) {
            // Free any allocated memory if parsing fails
		      free_element(element);
            // _free_list(*a_head);
//            free_list(*a_head);
			*a_pos = pos;
			printf("hel");
            return false;
        }

        // Create a new node for the element
        Node* newNode = (Node*)malloc(sizeof(Node));
        assert(newNode != NULL);

        newNode->element = element;
        newNode->next = NULL;

        // Link the node to the linked list
        if (*a_head == NULL) {
            *a_head = newNode; // Set the head of the linked list
        } else {
            prevNode->next = newNode;
        }

        prevNode = newNode;

        // Eat whitespace
    /*    while (isspace(*pos)) {
            pos++;
        }*/

        // Check for the end of the list ']'
        if (*pos == ']') {
            pos++; // Move to the next character after ']'
			*a_pos = pos;
            return true; // Successfully parsed the list
        }

        // Check for the list element separator ','
        if (*pos == ',') {
            pos++; // Move to the next character after ','
        } else {
            // Invalid list syntax (unexpected character)
			free_element(element);
            // _free_list(*a_head);
			*a_pos = pos;
//            return false;
            break;
        }
    }

    // If we reach here, the end of the string was reached before finding ']'
    //free_list(*a_head);
/*	*a_pos = pos;
	printf("he", *a_pos);*/
	//free_element(element);
	printf("\nhl\n");
    return false;
}
	





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
/*if (a_value == NULL || a_pos == NULL || *a_pos == NULL || **a_pos == '\0') {
        return false; // Invalid input arguments
    }

    const char* pos = *a_pos;
    int sign = 1;

    // Handle the sign (if present)
    if (*pos == '-') {
        sign = -1;
        pos++;
    } else if (*pos == '+') {
        pos++;
    }

    // Parse the integer value
    int result = 0;
    while (*pos >= '0' && *pos <= '9') {
        result = result * 10 + (*pos - '0');
        pos++;
    }

    // Check if there was at least one digit
    if (pos == *a_pos) {
        return false; // No valid integer literal found
    }

    // Update output arguments
    *a_value = result * sign;
    *a_pos = pos;

    return true;*/
}


bool parse_string(char** a_string, const char** a_pos) {
    if (**a_pos != '"') {
        return false;
    } 
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
/*
	
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
	}*/

/*if (a_element == NULL || a_pos == NULL || *a_pos == NULL) {
        return false; // Invalid input arguments
    }*/

    // Eat whitespace
    while (isspace(**a_pos)) {
        (*a_pos)++;
    }

    // Check the type of the element based on the next character
    if (isdigit(**a_pos) || **a_pos == '-') {
        a_element->type = ELEMENT_INT;
        return parse_int(&(a_element->as_int), a_pos);
    } else if (**a_pos == '"') {
        a_element->type = ELEMENT_STRING;
        return parse_string(&(a_element->as_string), a_pos);
    } else if (**a_pos == '[') {
        a_element->type = ELEMENT_LIST;
		printf("in");
        return parse_list(&(a_element->as_list), a_pos);
    }
	printf("false");

    // If none of the above conditions match, it's an invalid element
    return false;
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        print_element(current->element);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
}

void print_element(Element element) {
    switch (element.type) {
        case ELEMENT_INT:
            printf("%d", element.as_int);
            break;
		case ELEMENT_STRING:
            printf("\"%s\"", element.as_string);
            break;
        case ELEMENT_LIST:
            printf("[");
            print_list(element.as_list);
            printf("]");
            break;
    }
}

void free_element(Element element) {
    switch (element.type) {
        case ELEMENT_STRING:
            free(element.as_string);
            break;
        case ELEMENT_LIST: {
         /* while (element.as_list) {
                Node* temp = element.as_list;
                element.as_list = element.as_list->next;
                free_element(temp->element);
				free(temp);
                
            } */
			_free_list(element.as_list);
        }
       default :
			break;
    }
}

