#include <stdio.h>
#include <stdlib.h>

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
int space_char(char c) {
  return (c == ' ' || c == '\t');
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
int non_space_char(char c) {
  return (c > 32 && c < 127);
}

/* Returns a pointer to the first character of the next
   space-separated token in zero-terminated str.  Return a zero pointer if
   str does not contain any tokens. */
char *token_start(char *str) {
  while (space_char(*str))
    str++;
  if (*str == '\0')
    return NULL;

  return str;
}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token) {
  while (non_space_char(*token))
    token++;
  return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str) {
  int count = 0;

  while (*str != '\0') {
    if ((str = token_start(str)) != NULL)
      count++;

    str = token_terminator(str);
  }
  return count;
}

/* Returns a fresly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {
  char *new_str = malloc(len+1);

  for (int i = 0; i < len; i++)
    new_str[i] = inStr[i];

  new_str[len] = '\0';
  return new_str;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char **tokenize(char* str) {
  int size = count_tokens(str);
  char **tokens = malloc((size + 1) * sizeof(char *));

  for (int i = 0; i < size; i++) {
    str = token_start(str);
    int len = token_terminator(str) - str;
    tokens[i] = copy_str(str, len);
    str += len;
  }
  tokens[size] = NULL;
  return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens) {
  int i = 0;
  while (tokens[i] != NULL) {
    printf("%s\n", tokens[i]);
    i++;
  }
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens) {
  int i = 0;
  while (tokens[i] != NULL) {
    free(tokens[i]);
    i++;
  }

  free(tokens);
}
