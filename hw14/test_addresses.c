#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "miniunit.h"
#include "addresses.h"

static char* _copy_string(const char* src_string) {
    size_t num_chars = strlen(src_string);
    char* dst_string = malloc(sizeof(*dst_string) * (num_chars + 1));
    return strcpy(dst_string, src_string);
}

static int _int_cmp(const void* p1, const void* p2) {
   const int* a_n1 = p1;
   const int* a_n2 = p2;
   return *a_n1 - *a_n2;
}

static int _string_cmp(const void* p1, const void* p2) {
   const char* str1 = p1;
   const char* str2 = p2;
   return strcmp(str1, str2);
}

static int _cmp_strings_by_length(const void* p1, const void* p2) {
   const char* str1 = p1;
   const char* str2 = p2;
   return strlen(str1) - strlen(str2);
}

static void _destroy_int(void* data) {
	/*Node* node = data;
	free(node);*/
}

static void _destroy_string(void* nod) {
//	printf("here");
	Node* node = nod;
    if (node != NULL) {
        free(node->a_value);
		//free(node);
    }
}

static void _print_int(const void* data) {
    printf("%d", *(const int*)data);
}

static void _print_string(const void* data) {
    printf("%s", (char*)data);
}


static int _test_stack_push_int() {
	mu_start();
	Node* head = NULL;
	int a = 1;
	int b = 2;
	stack_push(&head, &a);
	stack_push(&head, &b);
	print_list(head, _print_int);
	destroy_list(&head, _destroy_int);
	mu_check(head == NULL);
	mu_end();
}

static int _test_stack_push_str() {
	mu_start();
	Node* head = NULL;
	//char* a = "abc";
	//char* b = "def";
	stack_push(&head, _copy_string("abc"));
	stack_push(&head, _copy_string("def"));
	print_list(head, _print_string);
	destroy_list(&head, _destroy_string);
	mu_check(head == NULL);
	mu_end();
}

static int _test_stack_pop() {
	mu_start();
	Node* head = NULL;
	//char* a = "abc";
	//char* b = "def";
	//stack_push(&head, a);
	//stack_push(&head, b);
	//char* a = "abc";
 	//char* b = "def";
	stack_push(&head, _copy_string("abc"));
	stack_push(&head, _copy_string("def"));

	Node* top = stack_pop(&head);
	printf("%s\n", (char*)top->a_value);
	//mu_check((char*)top->a_value == b);
	free(top->a_value);
	free(top);
//	printf("new\n");
	print_list(head, _print_string);
	destroy_list(&head, _destroy_string);
	mu_check(head == NULL);
	mu_end();
}

static int _test_pq_enqueue() {
	mu_start();
Node* head = NULL;  // size 0
    pq_enqueue(&head, _copy_string("Reginald"), _cmp_strings_by_length);  // size 1
    pq_enqueue(&head, _copy_string("was"),      _cmp_strings_by_length);  // size 2
    pq_enqueue(&head, _copy_string("a"),        _cmp_strings_by_length);  // size 3
    pq_enqueue(&head, _copy_string("hatter"),   _cmp_strings_by_length);  // size 4

    // Print contents of the list:  a was hatter Reginald
    print_list(head, _print_string);
destroy_list(&head, _destroy_string);
mu_check(head == NULL);
	mu_end();
}

static int _test_pq_dequeue() {
	mu_start();
Node* head = NULL;  // size 0
    pq_enqueue(&head, _copy_string("d"), _cmp_strings_by_length);  // size 1
    pq_enqueue(&head, _copy_string("b"),      _cmp_strings_by_length);  // size 2
    pq_enqueue(&head, _copy_string("a"),        _cmp_strings_by_length);  // size 3
    pq_enqueue(&head, _copy_string("c"),   _cmp_strings_by_length);  // size 4

    // Print contents of the list:  a was hatter Reginald
	Node* rem = pq_dequeue(&head);
	printf("a-bas = %s\n", (char*)rem->a_value);
	free(rem->a_value);
	free(rem);
    print_list(head, _print_string);
destroy_list(&head, _destroy_string);
mu_check(head == NULL);
	mu_end();
}

static int _test_bst_int() {
	mu_start();
	BSTNode* root = NULL;
	destroy_tree(&root, _destroy_int);
	int a = 3;
	int b = 2;
	int c = 1;
	int d = 4;
	bst_insert(&root, &a, _int_cmp);
	bst_insert(&root, &b, _int_cmp);
	bst_insert(&root,  &c,_int_cmp);
	bst_insert(&root, &d, _int_cmp);
//	bst_insert(&root, arr[4], _int_cmp);
	print_tree(root, _print_int);
	destroy_tree(&root, _destroy_int);
	mu_check(root == NULL);
	mu_end();
}

static int _test_bst_str() {
	mu_start();
	BSTNode* root = NULL;
	bst_insert(&root,_copy_string("d"), _string_cmp);
	bst_insert(&root,_copy_string("c"), _string_cmp);
	bst_insert(&root,_copy_string("a"), _string_cmp);
	bst_insert(&root,_copy_string("b"), _string_cmp);
	print_tree(root, _print_string);
	destroy_tree(&root, _destroy_string);
	mu_check(root == NULL);
	mu_end();
}

static int _test_coverage() {
	mu_start();
	Node* head = NULL;
	head = stack_pop(&head);
	head = pq_dequeue(&head);
	destroy_list(&head, _destroy_int);
	mu_end();
}


int main(int argc, char* argv[]) {

	mu_run(_test_stack_push_int);

	mu_run(_test_stack_push_str);

	mu_run(_test_stack_pop);

	mu_run(_test_pq_enqueue);

	mu_run(_test_pq_dequeue);

	mu_run(_test_coverage);

	mu_run(_test_bst_int);

	mu_run(_test_bst_str);
	return EXIT_SUCCESS;
}

