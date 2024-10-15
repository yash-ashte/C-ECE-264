#ifndef __ADDRESSES_H__
#define __ADDRESSES_H__

typedef struct Node {
void* a_value;
struct Node* next;
} Node;

typedef struct BSTNode {
void* a_value;
struct BSTNode* left;
struct BSTNode* right;
} BSTNode;

void stack_push(Node** a_top, void* a_value);
Node* stack_pop(Node** stack);
void pq_enqueue(Node** a_head, void* a_value, int(*cmp_fn)(const void*, const void*));
Node* pq_dequeue(Node** a_head);
void print_list(Node* head, void (*print_fn)(const void*));
void destroy_list(Node** a_head, void (*destroy_fn)(void*));
void bst_insert(BSTNode** a_root, void* a_value,int(*cmp_fn)(const void*, const void*));
void print_tree(BSTNode* a_root,void (*print_fn)(const void*));
void destroy_tree(BSTNode** a_root, void (*destroy_fn)(void*));
/*void _destroy_int(void* data);
void _destroy_string(void* data);
void _print_int(const void* data);
void _print_string(const void* data);
int _int_cmp(const void* p1, const void* p2);
int _string_cmp(const void* p1, const void* p2);
int _string_length_cmp(const void* p1, const void* p2);
char* _copy_string(const char* src_string);*/

#endif /* end of include guard: __ADDRESSES_H__ */

