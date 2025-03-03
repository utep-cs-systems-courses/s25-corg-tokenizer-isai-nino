#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int compare_str(char *str1, char *str2) {
  while (*str2 != '\0') {
    if (*str1 != *str2)
      return 0;
    *str1++;
    *str2++;
  }
  return 1;
}

int main()
{
  puts("---- Welcome to the tokenizer ----");
  puts("- Commands: history | !id | quit -");
  puts("----------------------------------");
  List *root = init_history();

  while (1) {
    char string[70];
    printf("> ");
    fgets(string, sizeof(string), stdin);

    // Handles if the user only pressed Enter
    for (int i = 0; string[i] != '\0'; i++) {
      if (string[i] == '\n') {
        string[i] = '\0';
        break;
      }
    }

    // Saving to history
    char **tokens = tokenize(string);
    for (int i = 0; ; i++) {
      if (tokens[i] == NULL)
        break;
      add_history(root, tokens[i]);
    }

    // Identifying commands
    switch (string[0]) {
      // History command
      case 'h':
        if (compare_str(string, "history"))
          print_history(root);
        break;
      // Id history command
      case '!':
        char *endptr;
        int id = strtol(&string[1], &endptr, 10);
        char *item = get_history(root, id);

        if (item == NULL) {
          printf("Not a valid id\n");
        } else {
          printf("%d %s\n", id, item);
        }
        break;
      // Quit command
      case 'q':
        if (compare_str(string, "quit")) {
          free_tokens(tokens);
          goto done;
        }
        break;
      default:
    }
  }

  done:
  free_history(root);
  return 0;
}
