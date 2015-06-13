#pragma once

struct list;

typedef struct list list;
typedef list* plist;

plist list_create();

plist list_last(plist list);

void list_add(plist list, void* val);

void list_remove(plist list, void* val);

void* list_remove_node(plist list);

void list_destroy(plist list);
