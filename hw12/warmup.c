#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _Node {
	int value;
	struct _Node* next;
} Node;

void stack_push(Node** a_top, int value) {
	// TODO: implement function
	Node *new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = value;
	new->next = *a_top;
	*a_top = new;
}

void print_list(const Node* head) {
	// TODO: implement function
	while(head->next != NULL) {
		printf("%d, ", head->value);
		head = head->next;
	}
	printf("%d\n", head->value);
}

void destroy_list(Node** a_head) {
	// TODO: implement function
	Node* current = *a_head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *a_head = NULL;	
}

int main(int argc, char* argv[]) {
	Node* top = NULL;
	stack_push(&top, 7);
	print_list(top); // prints "7"
	stack_push(&top, 1);
	print_list(top); // prints "1, 7"
	stack_push(&top, 5);
	print_list(top); // prints "5, 1, 7"

	destroy_list(&top); // no memory leaks

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
