/**
 * Methods and declarations for Queue and Node
 */

#include "constants.h"
#include "thread.h"

/**
 * nodes for the queue
 */
typedef struct _node
{
	tcb content;
	struct _node *prev;
	struct _node *next;
} node;

/**
 * Add a node to the end of the queue
 * @param head of the queue
 * @param content for the new node
 * @return true if successful else false
 */
bool add(node * head, tcb * content);

/**
 * deletes the given node from the queue
 * @param head of the queue
 * @param node to delete
 * @return true if successful
 */
bool del(node * head, node * to_delete);

/**
 * Moves the head node to the end of the queue 
 * @param pointer the head
 * @return true if succesful, else false
 */
bool rotate(node * head);