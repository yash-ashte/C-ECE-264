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


bool read_json(const char* filename, Element* a_element) {
	assert(filename != NULL);
	assert(a_element != NULL);

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file '%s' for reading!\n", filename);
        return false;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to read the file
    char* file_contents =  malloc(sizeof(char) * (file_size + 1));
    assert(file_contents != NULL);
      

    // Read the file contents into the allocated memory
    size_t read_size = fread(file_contents, 1, file_size, file);
    file_contents[read_size] = '\0';

    // Close the file
    fclose(file);

    // Parse the JSON element from the file contents
    const char* pos = file_contents;
    if (!parse_element(a_element, &pos)) {
        fprintf(stderr, "Invalid JSON element in file '%s'!\n", filename);
        free(file_contents);
        return false;
    }

    // Check for non-whitespace trailing characters
    while (*pos != '\0') {
        if (!isspace(*pos)) {
            fprintf(stderr, "File '%s' contains non-whitespace trailing characters!\n", filename);
            free_element(*a_element);
            free(file_contents);
            return false;
        }
        pos++;
    }

    // Free the allocated memory for file contents
    free(file_contents);

    return true;
}



bool parse_null(char const** a_pos) {
	assert(a_pos != NULL);
	//assert(*a_pos != NULL);
	const char* pos = *a_pos;
	while (*pos == ' ') {
		pos++;
	}
	if (*pos == 'n') {
		++pos;
		if (*pos == 'u') {
			++pos;
			if (*pos == 'l') {
				++pos;
				if (*pos == 'l') {
					++pos;
					*a_pos = pos;
					return true;	
				}
			}
		}
	}
	*a_pos = pos;
	return false;
}

bool parse_bool(bool* a_value, const char** a_pos) {
    // Check for null pointers to avoid crashes
    assert(a_value != NULL);
	assert(a_pos != NULL);
	assert(*a_pos != NULL);
    const char* pos = *a_pos;
    while (*pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r') {
        pos++;
    }
	if (*pos == 't') {
		pos++;
		if (*pos == 'r') {
			pos++;
			if (*pos == 'u') {
				pos++;
				if (*pos == 'e') {
					pos++;
					*a_pos = pos;
					*a_value = true;
					return true;
					
				}
			}
		}
	}  else if (*pos == 'f') {
		pos++;
		if (*pos == 'a') {
			pos++;
			if (*pos == 'l') {
				pos++;
				if (*pos == 's') {
					pos++;
					if (*pos == 'e') {
						pos++;
						*a_pos = pos;
						*a_value = false;
						return true;
						
					}
				}
			}
		}
	}
	 // If not a valid boolean literal, return false
	*a_pos = pos;
    return false;
}



void _free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head->next;
        free_element(head->element); // Free the element
        free(head);
        head = temp;
    }
}


bool parse_list(Node** a_head, const char** a_pos) {
/*if (a_head == NULL || a_pos == NULL || *a_pos == NULL) {
        return false;
    }	*/
 /*   const char* pos = *a_pos;

    while (isspace(*pos)) {
        pos++;
    }
    if (*pos != '[') {
		*a_pos = pos;
        return false;
    }

    pos++;

    *a_head = NULL;
    while (*pos != ']') {
        while (isspace(*pos) || *pos == ',') {
            pos++;
        }
        if (*pos == ']') {
            break;
        }
        Element element;
        if (!parse_element(&element, &pos)) {

            _free_list(*a_head);
            *a_head = NULL;
			*a_pos = pos;
            return false;
        }


        Node* new_node = malloc(sizeof(*new_node));
        assert(new_node != NULL);

        new_node->element = element;
        new_node->next = NULL;

        // Update the linked list
        if (*a_head == NULL) {
            *a_head = new_node;
        } else {
            Node* tail = *a_head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = new_node;
        }
    }

    // Move to the next character after ']'
    pos++;

    // Update the position pointer
    *a_pos = pos;

    return true;*/

/*if (a_head == NULL || a_pos == NULL || *a_pos == NULL) {
        return false;
    }*/

    // Eat whitespace
    while (isspace(**a_pos)) {
        (*a_pos)++;
    }

    // Check if it starts with '['
    if (**a_pos != '[') {
        return false;
    }

    // Move past the '['
    (*a_pos)++;

    *a_head = NULL;
    Node* current = NULL;
	
	if (**a_pos == ']') {
        (*a_pos)++; // Move past the ']'
        return true;
    }

    while (true) {
        // Parse the element
		Element element;
        if (!parse_element(&element, a_pos)) {
            if (current != NULL) {
                _free_list(*a_head); // Free the list if an error occurs
            }
            return false;
        }

        // Create a new node for the linked list
        Node* new_node = (Node*)malloc(sizeof(Node));
        assert(new_node != NULL);

        new_node->element = element;
        new_node->next = NULL;

        // Add the node to the linked list
        if (current == NULL) {
            *a_head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = current->next;
        }

        // Eat whitespace
        while (isspace(**a_pos)) {
            (*a_pos)++;
        }

        // Check if it's the end of the list or there's a comma separator
        if (**a_pos == ']') {
            (*a_pos)++; // Move past the ']'
            return true;
        } else if (**a_pos == ',') {
            (*a_pos)++; // Move past the ','
        } else {
            _free_list(*a_head);
            return false;
        }
    }
}

bool parse_int(int* a_value, const char** a_pos) {
    // Check for null pointers to avoid crashes
	assert(a_value != NULL);
	assert(a_pos != NULL);
	assert(*a_pos != NULL);

    const char* pos = *a_pos;
    bool is_negative = false;

    // Skip any leading whitespace
    while (*pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r') {
        pos++;
    }

    // Check if the number is negative
    if (*pos == '-') {
        is_negative = true;
        pos++;
    }

    // Check if there is at least one digit after the optional sign
    if (!isdigit(*pos)) {
		*a_pos = pos;
        return false;
    }

    int value = 0;
    while (isdigit(*pos)) {
        // Convert the character to an integer and update the value
        value = value * 10 + (*pos - '0');
        pos++;
    }

    // Apply the sign if the number is negative
    if (is_negative) {
        value = -value;
    }

    // Set the output value and update the position pointer
    *a_value = value;
    *a_pos = pos;

    return true;
}


bool parse_string(char** a_string, const char** a_pos) {
	assert(a_string != NULL);
	assert(a_pos != NULL);
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

    *a_string = malloc((length + 1) * sizeof(char));
    assert(*a_string != NULL);
    for (size_t i = 0; i < length; i++) {
        (*a_string)[i] = (*a_pos)[i];
    }
    (*a_string)[length] = '\0';

    *a_pos = end_pos + 1;
    return true;
}




bool parse_element(Element* a_element, char const** a_pos) {
    // Eat whitespace
	assert(a_element != NULL);
	assert(a_pos != NULL);
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
	    return parse_list(&(a_element->as_list), a_pos);
    } else if (**a_pos == 't' || **a_pos == 'f') {
		a_element->type = ELEMENT_BOOL;
		return parse_bool(&(a_element->as_bool), a_pos);
	} else if (**a_pos == 'n') {
		a_element->type = ELEMENT_NULL;
		return parse_null(a_pos);
	} 

    return false;
}

void _print_list(Node* head, FILE* file) {
    Node* current = head;
    while (current != NULL) {
        print_element_to_file(current->element, file);
        if (current->next != NULL) {
            fprintf(file, ", ");
        }
        current = current->next;
    }
}

void print_element_to_file(Element element, FILE* file) {
	assert(file != NULL);
	switch (element.type) {
        case ELEMENT_INT:
            fprintf(file, "%d", element.as_int);
            break;
		case ELEMENT_STRING:
            fprintf(file, "\"%s\"", element.as_string);
            break;
        case ELEMENT_LIST:
            fprintf(file,"[");
            _print_list(element.as_list, file);
            fprintf(file, "]");
            break;
		case ELEMENT_BOOL:
			if (element.as_bool == 1) {
				fprintf(file, "true");
			}
			else if (element.as_bool == 0) {
				fprintf(file, "false");
			}
			break;
		case ELEMENT_NULL:
			fprintf(file, "null");
			break;
    }
}

void write_json(const char* filename, Element element) {
	assert(filename != NULL);
    FILE* file = fopen(filename, "w");
    assert(file != NULL);
    print_element_to_file(element, file);
    fclose(file);
	file = NULL;
}

void print_element(Element element) {
	print_element_to_file(element, stdout);
}

void free_element(Element element) {
    // Free the contents of the Element based on its type
    switch (element.type) {
        case ELEMENT_INT:
            // Nothing to free for an integer
            break;
        case ELEMENT_STRING:
            // Free the string if it exists
            if (element.as_string != NULL) {
                free(element.as_string);
            }
            break;
        case ELEMENT_LIST:
				if (element.as_list != NULL) {
					_free_list(element.as_list);
				}
  //          }
            break;
		default:
			break;
    }
}

