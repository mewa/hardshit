#include <shared_ptr.h>
#include <stdlib.h>

list* sharedList = NULL;

struct shared_ptr {
  size_t refCount;
  void* ptr;
  void (*destructor)(void);
};

shared_ptr* shared_ptr_create(void* obj, void (*destructor)(void))  {
  shared_ptr* ptr = malloc(sizeof(shared_ptr));
  ptr->ptr = obj;
  ptr->destructor = destructor;
  return ptr;
}
