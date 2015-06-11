struct stack;
typedef struct stack stack;


/*
  Creates a new stack object
 */
stack* stack_create();

/*
  Pushes a value up the stack
 */
stack* stack_push(stack* stack, void* value);

/*
  Returns a value from the stack and adjusts its root
 */
stack* stack_pop(stack* stack, void* value);

/*
  Destroys stack object
 */
void stack_destroy(stack* stack);
