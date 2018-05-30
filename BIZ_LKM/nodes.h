#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct node {
  int64_t a;
  int64_t c;
  int64_t m;
  struct node *next;
} node;

node * init_node(int64_t a, int64_t c, int64_t m);
void add_node(int64_t a, int64_t c, int64_t m, node **h);
void clear_list(node **h);
void del_node(int64_t a, int64_t c, int64_t m, node **h);
int list_len(node *h);
void print_list(node *h);