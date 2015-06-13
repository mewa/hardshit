#pragma once

#include <list.h>
#include <string.h>

list* sharedList;

struct shared_ptr;

typedef struct shared_ptr shared_ptr;

shared_ptr* shared_ptr_create(void* obj, void (*destructor)(void));
