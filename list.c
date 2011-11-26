/**
 * CS 2110 - Fall 2011 - Homework #11
 * Edited by: Brandon Whitehead
 *
 * list.c: Complete the functions!
 **/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
  list *l = malloc(sizeof(list));
  l->head = NULL;
  l->size = 0;
  return l;
}

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
  node *n = malloc(sizeof(node));
  n->data = data;
  n->prev = NULL;
  n->next = NULL;
  return n;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
  node *n = create_node(data);
  if (!llist->size) {
    n->next = n;
    n->prev = n;
  } else {
    node *head = llist->head;
    node *prev = head->prev;
    n->next = head;
    n->prev = head->prev;
    head->prev = n;
    prev->next = n;
  }
  llist->head = n;
  llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
  node *n = create_node(data);
  if (!llist->size) {
    n->next = n;
    n->prev = n;
  } else {
    node *head = llist->head;
    node *prev = head->prev;
    n->next = head;
    n->prev = head->prev;
    head->prev = n;
    prev->next = n;
  }
  llist->size++;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
  if (llist->size) {
    node *head = llist->head;
    node *next = head->next;
    node *prev = head->prev;
    llist->head = next;
    next->prev = prev;
    prev->next = next;
    llist->size--;
    free_func(head->data);
    free(head);
    return 0;
  } else {
    return -1;
  }
    /// @todo Implement
    /// @note remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_index
  *
  * Removes the indexth node of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param index index of the node to remove.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_index(list* llist, int index, list_op free_func)
{
  if (!llist->size) {
    return -1;
  }

  node *current = llist->head;
  for (int i=0; i<index; i++) {
    current = current->next;
  }

  node *next = current->next;
  node *prev = current->prev;
  prev->next = next;
  next->prev = prev;

  llist->size--;

  free_func(current);
  free(current);

  return 0;
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
  if (!llist->size) {
    return -1;
  }

  node *head = llist-> head;
  node *tbr = head->prev; // to be removed
  node *nb = tbr->prev; // new back
  head->prev = nb;
  nb->next = head;

  llist->size--;

  free_func(tbr);
  free(tbr);

  return 0;
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_data
  *
  * Removes ALL nodes whose data is EQUAL to the data you passed in or rather when the comparison function returns true (!0)
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list
  * @param data data to compare to.
  * @param compare_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see equal_op.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_data(list* llist, const void* data, equal_op compare_func, list_op free_func)
{
  int removed = 0;
  node *current = llist->head;
  node *next = current->next;
  node *prev = current->prev;

  for (int i=0; i<llist->size; i++) {
    if (compare_func(data, current->data)) {
      next->prev = prev;
      prev->next = next;
      free_func(current->data);
      free(current);
      current = next;
      removed++;
    } else {
      current = current->next;
    }
    next = current->next;
    prev = current->prev;
  }
  llist->size-=removed;
  return removed;
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
  if (!llist->size) {
    return 0;
  }

  int removed = 0;
  node *current = llist->head;
  node *next = current->next;
  node *prev = current->prev;

  for (int i=0; i<llist->size; i++) {
    if (pred_func(current->data)) {
      next->prev = prev;
      prev->next = next;
      free_func(current);
      free(current);
      current = next;
      removed++;
    } else {
      current = current->next;
    }
    next = current->next;
    prev = current->prev;
  }

  llist->size-=removed;
  return removed;

    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
  if (llist->size) {
    return llist->head->data;
  } else {
    return NULL;
  }
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
}

/** get_index
  *
  * Gets the data at the indexth node of the linked list
  * If the list is empty or if the index is invalid return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the indexth node in the linked list or NULL.
  */
void* get_index(list* llist, int index)
{
  if (!llist->size || index >= llist->size) {
    return NULL;
  }
  
  node *current = llist->head;
  for (int i=0; i<index; i++) {
    current = current->next;
  }

  return current->data;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
  if (!llist->size) {
    return NULL;
  }

  node *end = llist->head->prev;
  return end->data;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
  if (llist->size == 0 && llist->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
  return llist->size;
}

/** find_occurence
  *
  * Tests if the search data passed in is in the linked list.
  *
  * @param llist a pointer to a linked list.
  * @param search data to search for the occurence.
  * @param compare_func a pointer to a function that returns true if two data items are equal @see equal_op.
  * @return 1 if the data is indeed in the linked list 0 otherwise.
  */
int find_occurrence(list* llist, const void* search, equal_op compare_func)
{
  node *current = llist->head;
  for (int i=0; i<llist->size; i++) {
    if (compare_func(search, current->data)) {
      return 1;
    }
  }
  return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func)
{
  node *current = llist->head;
  node *next = current->next;

  for (int i=0; i<llist->size; i++) {
    free_func(current->data);
    free(current);
    current = next;
    next = current->next;
  }

  llist->size=0;
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
  node *current = llist->head;
  for (int i=0; i<llist->size; i++) {
    do_func(current->data);
    current = current->next;
  }
    /// @todo Implement
}
