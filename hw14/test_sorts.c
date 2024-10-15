#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "sorts.h"


static int _test_create_pq() {
	mu_start();
	//---
    PriorityQueue pq = create_pq((int[2]) { 4, 2 }, 2);	
	mu_check(pq.head->value == 2);
	mu_check(pq.head->next->value == 4);
	mu_check(pq.head->next->next == NULL);
	destroy_pq(&pq);
	//---
	mu_end();
}

static int _test_sort_pq() {
	mu_start();
	//---
	int og[] = {8,2,5,1,9};
	pq_sort_array(og, 5);
	mu_check(og[0] == 1);
	mu_check(og[1] == 2);
	mu_check(og[2] == 5);
	mu_check(og[3] == 8);
	mu_check(og[4] == 9);
	//---
	mu_end();
}

static int _test_create_bst() {
	mu_start();
	//---
    BST bst = create_bst((int[7]) { 4,2,6,1,3,5,}, 7);	
	mu_check(bst.root->value == 4);
	mu_check(bst.root->left->value == 2);
	mu_check(bst.root->right->value == 6);
	destroy_bst(&bst);
//	free(bst.root);
	//---
	mu_end();
}

static int _test_sort_bst() {
	mu_start();
	//---
	int og[] = {8,2,5,1,9};
	tree_sort_array(og, 5);
	mu_check(og[0] == 1);
	mu_check(og[1] == 2);
	mu_check(og[2] == 5);
	mu_check(og[3] == 8);
	mu_check(og[4] == 9);
	//---
	mu_end();

}

int main(int argc, char* argv[]) {
	mu_run(_test_create_pq);
	mu_run(_test_sort_pq);
	mu_run(_test_create_bst);
	mu_run(_test_sort_bst);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
