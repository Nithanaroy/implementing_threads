#include "q.h"
#include <assert.h>

/**
 * Test cases for intializing the queue
 */

void test_create_queue() {

}


/**
 * Test cases for other miscellaneous functions in q.h
 */

void test_create_node() {

}

/**
 * Test cases for add items to the queue function
 */

void test_add_first_element() {

}

void test_add_element_with_incorrect_args() {

}

void test_add_element() {

}


/**
 * Test cases for delete element from queue function
 */

/**
 * a test that checks delete function by passing incorrect arguments
 * pre-condition: create_node() function works correctly
 */
void test_delete_element_with_incorrect_args() {
	// should return false if either of the args is in correct
	assert(DelQ(NULL, NULL) == false);

	// should return false if either of the args is in correct
	TCB_t * head = create_node();
	assert(DelQ(&head, NULL) == false);

	// should return false if either of the args is in correct
	TCB_t * node = create_node();
	assert(DelQ(NULL, node) == false);

	printf("test_delete_element_with_incorrect_args() passed\n");
}

/**
 * a test that checks delete function by deleting the only element head, in the queue
 * pre-condition: create_node() and InitQ() work correctly
 */
void test_delete_only_element() {
	// only head is present in the queue and we want to delete it
	TCB_t * head = create_node();
	InitQ(head);
	assert(DelQ(&head, head) == true);
	assert(head == NULL);

	printf("test_delete_only_element() passed\n");
}

/**
 * a test that checks delete function when the queue is empty
 * pre-condition: create_node() and InitQ() work correctly
 */
void test_delete_element_from_empty_queue() {
	TCB_t * head = create_node();
	InitQ(head);
	DelQ(&head, head); // empty list now

	TCB_t * node = create_node();
	// trying to delete some element from an empty queue
	assert(DelQ(&head, node) == false);

	printf("test_delete_element_from_empty_queue() passed\n");
}

void test_delete_head() {

}

void test_delete_intermediate_element() {

}

void test_delete_last_element() {

}


/**
 * Test cases that checks the rotate queue funtionality
 */

/**
 * a test to check if rotate queue handles invalid arguments correctly
 */
void test_rotate_queue_with_invalid_args() {
	assert(RotateQ(NULL) == false);

	printf("test_rotate_queue_with_invalid_args() passed\n");
}

/**
 * a test to check if rotate queue handles empty queues
 * pre-condition: delete single element queue works correctly
 * pre-condition: create_node() works correctly
 * pre-condition: InitQ() works correctly
 */
void test_rotate_empty_queue() {
	TCB_t * head = create_node();
	InitQ(head);
	DelQ(&head, head); // empty queue

	assert(RotateQ(&head) == true);

	printf("test_rotate_empty_queue() passed\n");
}

/**
 * a test to check rotate queue functionality when all arguments are passed correctly, happy case
 */
void test_rotate_queue() {

}




int main(void) {
	printf("\n");
	test_create_queue();
	test_create_node();
	
	test_add_first_element();
	test_add_element_with_incorrect_args();
	test_add_element();
	
	test_delete_element_with_incorrect_args();
	test_delete_only_element();
	test_delete_element_from_empty_queue();
	test_delete_head();
	test_delete_intermediate_element();
	test_delete_last_element();

	test_rotate_queue_with_invalid_args();
	test_rotate_empty_queue();
	test_rotate_queue();

	printf("\n");
	return 0;
}