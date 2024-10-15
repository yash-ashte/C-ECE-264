#ifndef __SORTS_H__
#define __SORTS_H__

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct _Node {
	int size;
	Node* head;
} PriorityQueue;

typedef struct BSTNode {
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BST {
    BSTNode* root;
    int size;
} BST;


PriorityQueue create_pq(const int* array, size_t size);
void destroy_pq(PriorityQueue* a_pq);
void pq_sort_array(int* array, size_t size);
BST create_bst(const int* array, size_t size);
void destroy_bst(BST* a_bst);
void tree_sort_array(int* array, size_t size);

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */


#endif /* end of include guard: __SORTS_H__ */
