#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "clog.h"
#include "sorts.h"

void pq_sort_array(int* array, size_t size) {
	// Step 1: Create the priority queue
    PriorityQueue pq = create_pq(array, size);

    // Step 2: Traverse the queue and store sorted values in the array
    Node* currentNode = pq.head;
    size_t i = 0;

    while (currentNode != NULL) {
        array[i] = currentNode->value;
        i++;
//        Node* temp = currentNode;
        currentNode = currentNode->next;
      // Free the allocated node
    }

    // Step 3: Destroy the priority queue
    destroy_pq(&pq);
}

PriorityQueue create_pq(const int* array, size_t size) {
    PriorityQueue pq;
    pq.head = NULL;
    pq.size = 0;

    if (size == 0 || array == NULL)
        return pq;

    // Create the first node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = array[0];
    newNode->next = NULL;

    pq.head = newNode;
    pq.size++;

    // Iterate over the remaining elements and insert them in sorted order
    for (size_t i = 1; i < size; i++) {
        Node* currentNode = pq.head;
        Node* prevNode = NULL;

        // Find the correct position to insert the element in the sorted list
        while (currentNode != NULL && array[i] > currentNode->value) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        // Create a new node and insert it into the sorted list
        newNode = (Node*)malloc(sizeof(Node));
        newNode->value = array[i];
        newNode->next = currentNode;

        if (prevNode == NULL)
            pq.head = newNode;
        else
            prevNode->next = newNode;

        pq.size++;
    }

    return pq;
}


void destroy_pq(PriorityQueue* pq) {
    Node* currentNode = pq->head;
    while (currentNode != NULL) {
        Node* temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
    pq->head = NULL;
    pq->size = 0;
}


BST create_bst(const int* array, size_t size) {
    BST bst;
    bst.root = NULL;
    bst.size = 0;

    if (size == 0 || array == NULL)
        return bst;

    // Create the root node
    BSTNode* rootNode = (BSTNode*)malloc(sizeof(BSTNode));
    rootNode->value = array[0];
    rootNode->left = NULL;
    rootNode->right = NULL;

    bst.root = rootNode;
    bst.size++;

    // Insert the remaining elements into the BST
    for (size_t i = 1; i < size; i++) {
        int value = array[i];
        BSTNode* currentNode = bst.root;
        BSTNode* parentNode = NULL;

        // Find the correct position to insert the element in the BST
        while (currentNode != NULL) {
            parentNode = currentNode;

            if (value < currentNode->value)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }

        // Create a new node and insert it into the BST
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;

        if (value < parentNode->value)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;

        bst.size++;
    }

    return bst;
}

void _destruction_recursive(BSTNode* node) {
    if (node == NULL)
        return;

    _destruction_recursive(node->left);
    _destruction_recursive(node->right);

    free(node);
}



void destroy_bst(BST* bst) {
    if (bst->root != NULL)
       _destruction_recursive(bst->root);

    bst->root = NULL;
    bst->size = 0;
//	free(bst->root);
}

void _in_order_traversal(BSTNode* node, int* array, size_t* index) {
    if (node == NULL)
        return;

    _in_order_traversal(node->left, array, index);
    array[*index] = node->value;
    (*index)++;
    _in_order_traversal(node->right, array, index);
}


void tree_sort_array(int* array, size_t size) {
    // Step 1: Create the BST
    BST bst = create_bst(array, size);

    // Step 2: Use in-order traversal to store sorted values in the array
    size_t index = 0;
    _in_order_traversal(bst.root, array, &index);

    // Step 3: Destroy the BST
    destroy_bst(&bst);
}








/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
