/**
 * Methods and declarations for Thread
 */

#include <stdint.h>
 #include "q.h"

typedef struct _tcb
{
	/* pointed to PC */
	uint32_t pc;
	// uint64_t pc; // TODO
} tcb;

/**
 * initializes a thread
 * @param the function to run
 */
void start(void (*function) (void));

/**
 * runs the thread
 */
void run();

/**
 * switches the context
 */
void yield();