#include <stack.h>
#include <stdlib.h>

struct stack {
  stack* root;
  void* value;
};

typedef stack stack_t;

stack* stack_create() {
 stack* stack = malloc(sizeof(stack));
 stack->root = NULL;
 return stack;
}

stack* stack_push(stack* stack, void* value) {
  stack_t* newStack = stack_create();
  if (stack) {
    newStack->root = stack;
  }
  newStack->value = value;
  return newStack;
}

stack* stack_pop(stack* stack, void* value) {
  value = stack->value;
  stack_t* tmp = stack;
  stack = stack->root;
  stack_destroy(tmp);
  return stack;
}

int stack_contains(stack* stack, void* value) {
  while (stack) {
    if (stack->value == value) {
      return 0;
    }
    stack = stack->root;
  }
  return 1;
}

void stack_destroy(stack* stack) {
  free(stack);
}
