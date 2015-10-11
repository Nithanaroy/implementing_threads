#include "q.h"

void print_q(TCB_t * head) {
	if (head == NULL)
	{
		printf("Empty List\n");
		return;
	}
	TCB_t * start = head;
	while (head != start) {
		printf("%d ", head -> dummy);
		head = head -> next;
	}
	printf("\n");
}

int main(void) {
	TCB_t * head = new_node();
	init_q(head, 1);
	add(head, 0, 2);
	add(head, 0, 3);
	add(head, 0, 4);
	add(head, 0, 5);
	add(head, 0, 6);
	print_q(head);
	return 0;
}