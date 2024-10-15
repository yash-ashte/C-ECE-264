#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "clog.h"
#include "addresses.h"


/*ze_t num_chars = strlen(src_string);
    char* dst_string = malloc(sizeof(*dst_string) * (num_chars + 1));
    return strcpy(dst_string, src_string);
}

int _int_cmp(const void* p1, const void* p2) {
   const int* a_n1 = p1;
   const int* a_n2 = p2;
   return *a_n1 - *a_n2;
}

int _string_cmp(const void* p1, const void* p2) {
   const char* str1 = p1;
   const char* str2 = p2;
   return strcmp(str1, str2);
}

int _string_length_cmp(const void* p1, const void* p2) {
   const char* str1 = p1;
   const char* str2 = p2;
   return strlen(str1) - strlen(str2);
}*/

void bst_insert(BSTNode** a_root, void* a_value, int (*cmp_fn)(const void*, const void*))
{
    assert(a_root != NULL);
    if (*a_root == NULL) {
        BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
        assert(new_node != NULL);
        new_node->a_value = a_value;
        new_node->left = NULL;
        new_node->right = NULL;
        *a_root = new_node;
        return;
    }
    int cmp_result = cmp_fn(a_value, (*a_root)->a_value);
    if (cmp_result < 0) {
	    bst_insert(&((*a_root)->left), a_value, cmp_fn);
    } else {
        bst_insert(&((*a_root)->right), a_value, cmp_fn);
    }
}

void print_tree(BSTNode* root, void (*print_fn)(const void*))
{
    if (root != NULL) {
        print_tree(root->left, print_fn);
        print_fn(root->a_value);
		printf("\n");
        print_tree(root->right, print_fn);
    }
	return;
}

void destroy_tree(BSTNode** a_root, void (*destroy_fn)(void*))
{
    if (*a_root == NULL) {
        return;
    }
	if ((*a_root)->left != NULL) {
    	destroy_tree(&((*a_root)->left), destroy_fn);
	}
	 
	if ((*a_root)->right != NULL) {
    	destroy_tree(&((*a_root)->right), destroy_fn);
	}
    destroy_fn(*a_root);
	free(*a_root);
    *a_root = NULL;
}

Node* pq_dequeue(Node** a_head)
{
    if (a_head == NULL || *a_head == NULL) {
        return NULL;
    }
    Node* removed_node = *a_head;
    *a_head = (*a_head)->next;
    removed_node->next = NULL;
    return removed_node;
}

void pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*))
{
    assert(a_head != NULL);

    Node* new_node = (Node*)malloc(sizeof(Node));
	assert(new_node != NULL);
    new_node->a_value = a_value;
    if ((*a_head == NULL) || (cmp_fn(a_value, (*a_head)->a_value) < 0)) {
        new_node->next = *a_head;
        *a_head = new_node;
        return;
    }
    Node* current = *a_head;
    while ((current->next != NULL) && (cmp_fn(a_value, current->next->a_value) >= 0)) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

void stack_push(Node** a_top, void* a_value)
{
    assert(a_top != NULL);
    Node* new_node = (Node*)malloc(sizeof(Node));
	assert(new_node != NULL);
//	printf("check %s\n", (char*) a_value);
    new_node->a_value = a_value;
//	printf("in - %s\n", (char*)a_value);
    new_node->next = *a_top;
    *a_top = new_node;
//	printf("end\n");
}

Node* stack_pop(Node** stack)
{
    if (stack == NULL || *stack == NULL) {
        return NULL; 
    }
    Node* top_node = *stack; 
    *stack = top_node->next;
    top_node->next = NULL;
    return top_node;
}

/*void _destroy_int(void* data) {}

void _destroy_string(void* nod) {
//	printf("here");
	Node* node = nod;
    if (node != NULL) {
//        free(node->a_value);
		free(node);
    }
}*/


void destroy_list(Node** a_head, void (*destroy_fn)(void*))
{
//	printf("print");
    if (a_head == NULL || *a_head == NULL) {
        return;
    }
	assert(a_head != NULL);
	assert(*a_head != NULL);

    Node* current = *a_head;
    Node* next;

    while (current != NULL) {
        next = current->next;
		printf("here2");
        destroy_fn(current);
		free(current);
        current = next;
    }

    *a_head = NULL;
}

/*void _print_int(const void* data) {
    printf("%d", *(const int*)data);
}

void _print_string(const void* data) {
    printf("%s", (char*)data);
}*/

void print_list(Node* head, void (*print_fn)(const void*))
{
    Node* current = head;

    while (current != NULL) {
        print_fn(current->a_value);
        printf("\n");
        current = current->next;
    }
//	printf("print here");
}


