//
// Created by mattias on 4/3/19.
//

#ifndef A3_LINKEDLIST_H
#define A3_LINKEDLIST_H


/* Given a node as prev_node, insert a new node after the given node */
void insertAfter(struct Node* prev_node, struct Node* new_node);

struct Node * removeItem(struct Node* node);

#endif //A3_LINKEDLIST_H
