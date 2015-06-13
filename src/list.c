#include <list.h>
#include <stdlib.h>

struct list {
	plist next;
	plist prev;
	void* value;
};

plist list_create() {
	plist list = malloc(sizeof(list));
	list->next = NULL;
	list->prev = NULL;
	list->value = NULL;
	return list;
}

plist list_last(plist list) {
	while (list) {
		if (list->next) {
			list = list->next;
		}
	}
	return list;
}

void list_add(plist list, void* val) {
	list = list_last(list);

	plist newl = list_create();
	newl->value = val;
	newl->prev = list;
	
	list->next = newl;	
}



void list_remove(plist list, void* val) {
	while (list) {
		if (list->value == val) {
			break;
		}
		list = list->next;
	}
	list_remove_node(list);
}

void* list_remove_node(plist list) {
	if (list->prev) {
		list->prev->next = list->next;
	}
	if (list->next) {
		list->next->prev = list->prev;
	}
	void* value = list->value;
	list_destroy(list);
	return value;
}

void list_destroy(plist list) {
	free(list);
}
