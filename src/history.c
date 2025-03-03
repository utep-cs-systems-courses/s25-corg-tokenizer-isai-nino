#include <stdio.h>
#include <stdlib.h>

typedef struct s_Item {
  int id;
  char *str;
  struct s_Item *next;
} Item;

typedef struct s_List {
  struct s_Item *root;
} List;

/* Initialize the linked list to keep the history. */
List* init_history() {
  List *history = malloc(sizeof(List));
  history->root = NULL;
  return history;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str) {
  Item *new_item = malloc(sizeof(Item));
  new_item->id = 1;
  new_item->str = str;
  new_item->next = NULL;

  if (list->root == NULL)
    list->root = new_item;

  else {
    Item *temp = list->root;

    while (temp->next != NULL)
      temp = temp->next;

    new_item->id = temp->id + 1;
    temp->next = new_item;
  }
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id) {
  Item *temp = list->root;

  while (temp != NULL) {
    if (temp->id == id)
      return temp->str;
    temp = temp->next;
  }
  return NULL;
}

/*Print the entire contents of the list. */
void print_history(List *list) {
  Item *temp = list->root;

  while (temp != NULL) {
    printf("%d %s\n", temp->id, temp->str);
    temp = temp->next;
  }
}

/*Free the history list and the strings it references. */
void free_history(List *list) {
  Item *temp = list->root;

  while (temp != NULL) {
    Item *next = temp->next;
    free(temp);
    temp = next;
  }

  free(list);
}
