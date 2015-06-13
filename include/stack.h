#pragma once

struct stack;
typedef struct stack stack;


/*
  Creates a new stack object
 */
stack* stack_create(void);

/*
  Pushes a value up the stack
 */
stack* stack_push(stack* stack, void* value);

/*
  Returns a value from the stack and adjusts its root
 */
stack* stack_pop(stack* stack, void* value);

/*
  Checks if stack contains passed object
*/
int stack_contains(stack* stack, void* value);

/*
  Destroys stack object
 */
void stack_destroy(stack* stack);
