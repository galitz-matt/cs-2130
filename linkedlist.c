/**
 * CSO1 HW8 Circularly Linked List Implementation
 *
 * Your Computing ID: ykk6rh
 */

//TODO: Remember to add include statement here. 
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

cll_node *cll_head(cll_node *list){
	if (list == NULL) {
		return NULL;
	}
	cll_node *iterator = list; // copy list, just to be safe I'm not completely certain about how the C local scope works
	while (!iterator->is_head) { // loop until head is found
		iterator = iterator->prev;
	}
	return iterator;
}


cll_node *cll_tail(cll_node *list) {
	if (list == NULL) {
		return NULL;
	}
	cll_node *iterator = list;
	while (!iterator->next->is_head) { // loop until tail is found
		iterator = iterator->next;
	}
	return iterator;
}


unsigned long cll_length(cll_node *list) {
	unsigned long length = 0;
	if (list == NULL) {
		return length;
	}
	cll_node *iterator = list;
	do {
		length++;
		iterator = iterator->next;
	} while (iterator != list); // loop until we're back where we began
	return length;
}

cll_node *cll_find(cll_node *list, int value) {
	if (list == NULL) {
		return NULL;
	}
	cll_node *iterator = list;
	do {
		if (iterator->value == value) {
			return iterator;
		}
		iterator = iterator->next;
	}
	while (iterator != list); // loop until value is found
	return iterator;
}


cll_node *cll_remove(cll_node *list) {
	if (!list) {
		return NULL;
	}
	cll_node *prev = list->prev;
	cll_node *next = list->next; // this is done for convenience
	if (list == next) {
		free(list);
		return NULL;
	}
	prev->next = next;
	next->prev = prev; // these reassigments break the links to the node to be removed
	if (list->is_head) { // if we're removing the head we make a new one
		next->is_head = 1;
		free(list);
		return next;
	}
	if (next->is_head) { // checks if node to be removed is the tail, if so we return NULL
		free(list);
		return NULL;
	}
	free(list);
	return next;
}


cll_node *cll_insert(int value, cll_node *list, int before) {  
	cll_node *node = malloc(sizeof(cll_node));
	node->is_head = 0;
	node->value = value;
	if (list == NULL) {
		node->prev = node;
		node->next = node;
		node->is_head = 1;
		return node;
	}
	if (before) {
		list = list->prev;
	}
	node->prev = list;
	node->next = list->next;
	list->next->prev = node;
	list->next = node;
	return node;
}


/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks.
 *
 * Reference solution provided with assignment description
 */
void cll_show(cll_node *list) {
    // Find the head of the linked list
    cll_node *head = cll_head(list);
    cll_node *ptr = head;
    // Print opening [
    putchar('[');
    // Loop through list printing values
    if (ptr) {
        do {
            if (!ptr->is_head) 
                printf(", "); // include a comma if not the first element
            if (ptr == list) 
                putchar('*'); // include * surrounding parameter element
            printf("%d", ptr->value);
            if (ptr == list) 
                putchar('*');
            ptr = ptr->next; // next pointer
        } while (ptr != head);
    }
    // Print closing ]
    puts("]");
}


int main(int argc, const char *argv[]) {

    // Example debugging code.  You should write other
    // tests, including testing corner cases.
    cll_node *x = NULL;
    putchar('A'); cll_show(x);
    x = cll_insert(25, x, 1);
    putchar('B'); cll_show(x);
    x = cll_insert(1, x, 0);
    putchar('C'); cll_show(x);
    x = cll_insert(98, x, 1);
    putchar('D'); cll_show(x);
    x = cll_insert(0, x, 1);
    putchar('E'); cll_show(x);
    x = cll_insert(-8, cll_tail(x), 0);
    putchar('F'); cll_show(x);
    cll_node *y = cll_head(x);
    putchar('G'); cll_show(y);
    printf("Length: %lu (or %lu)\n", cll_length(y), cll_length(x));
    x = cll_remove(x);
    putchar('H'); cll_show(x);
    putchar('I'); cll_show(y);
    x = cll_remove(cll_find(y, 98));
    putchar('J'); cll_show(x);
    putchar('K'); cll_show(y);
    cll_node *my_node = NULL;
    my_node = cll_remove(my_node);
    cll_show(my_node);
    my_node = cll_insert(1, my_node, 0);
    cll_show(my_node);
    my_node = cll_remove(my_node);
    cll_show(my_node);
    return 0;
}
