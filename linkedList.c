//
// Created by mattias on 4/3/19.
//

#include <malloc.h>
#include "structures.h"

/* Given a node as prev_node, insert a new node after the given node */
void insertAfter(struct Node* prev_node, struct Node * new_node)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL) {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;

    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

struct Node * removeItem(struct Node* node){
    struct Node * next = node->next;
    node->prev->next = next;
    if(node->next != NULL){
    	node->next->prev = node->prev;
    }
    free(node);
    return next;
}

