/**
 * Methods and declarations for Queue and Node
 */

#include "constants.h"
#include "tcb.h"
#include "malloc.h"

/**
 * Creates a new node with default settings
 * @return pointer to the new node created
 */
TCB_t * create_node() {
	TCB_t * new_node = (TCB_t *)malloc(sizeof(TCB_t));
	new_node -> next = NULL;
	new_node -> prev = NULL;
	// ALERT - context variable not set

	return new_node;
}

bool init_q(TCB_t * head) {
	// ALERT: we assume that the content of head, viz context, is set by the caller
	// here we only manage the links among the nodes in the queue
	head -> next = head;
	head -> prev = head;
}

/**
 * Add a node to the end of the queue
 * @param head of the queue
 * @param new node to add to the queue
 * @return true if successful else false
 */
bool add(TCB_t * head, TCB_t * new_node) {
	if (head == NULL || new_node == NULL)
	{
		return false;
	}

	// ALERT: we assume that the content of this node, viz context, is set by the caller
	// here we only manage the links among the nodes in the queue
	new_node -> next = head;
	new_node -> prev = head -> prev;

	head -> prev = new_node;
	new_node -> prev -> next = new_node;

	return true;
}

/**
 * deletes the given node from the queue
 * @param pointer to the, pointer of the head of the queue
 * @param node to delete
 * @return true if successful else false
 */
bool del(TCB_t ** head, TCB_t * to_delete) {
	// in correct arguments
	if (head == NULL || to_delete == NULL)
	{
		return false;
	}

	TCB_t * _head = *head;
	// queue is empty but user wants to delete a node!
	if (*head == NULL && to_delete != NULL)
	{
		return false;
	}

	// queue is not empty
	if (_head != NULL)
	{
		// head to be deleted
		if (to_delete == _head) {
			// head is the only element in the queue and that has to be deleted
			if (_head -> next == _head)
			{
				free(_head);
				*head = NULL; // empty queue
			}
			else {
				// head has to be deleted but it is not the only element
				TCB_t * old_head = _head; // head's next is the new head
				TCB_t * tail = old_head -> prev;

				*head = old_head -> next; // new head, have to update the original pointer, hence *head and not _head
				(*head) -> prev = old_head -> prev;
				tail -> next = _head;

				free(old_head);
			}
		}
		else {
			// non-head element to delete
			TCB_t * to_delete_prev = to_delete -> prev;
			TCB_t * to_delete_next = to_delete -> next;

			to_delete_prev -> next = to_delete -> next;
			to_delete_next -> prev = to_delete -> prev;

			free(to_delete);
		}
	}

	return true;
}

/**
 * Moves the head node to the end of the queue
 * @param pointer the head
 * @return true if succesful, else false
 */
bool rotate(TCB_t ** head) {
	if (head == NULL)
	{
		return false;
	}

	// if the queue is not empty
	if (*head != NULL)
	{
		// this is equivalent to, taking the head element and putting it at the end of the queue, in a 
		// circual doubly linked list
		*head = (*head) -> next;
	}

	return true;
}