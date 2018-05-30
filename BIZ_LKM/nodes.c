#include "nodes.h"

node *init_node(int64_t a, int64_t c, int64_t m)
{
  node *temp = (node *) malloc(sizeof(node));

  temp->a = a;
  temp->c = c;
  temp->m = m;

  temp->next = NULL;

  return (temp);
}
void add_node(int64_t a, int64_t c, int64_t m, node **h)
{
  node *temp = (node *) malloc(sizeof(node));
  
  temp->a = a;
  temp->c = c;
  temp->m = m;

  temp->next = (*h);

  (*h) = temp;
}
void clear_list(node **h)
{
  while(*h)
  {
    node *temp = (*h)->next;
    free(*h);
    (*h) = temp;
  }
}
void del_node(int64_t a, int64_t c, int64_t m, node **h)
{
  node *temp = (*h)->next;
  
  if((*h)->a == a && (*h)->c == c && (*h)->m == m) {
    free(*h);
    *h = temp;
    return;
  }

  node * temp1 = (*h);
  while(temp) {
    if(temp->a == a && temp->c == c && temp->m == m) {
      temp1->next = temp->next;
      free(temp);
      return;
    }
    temp1 = temp1->next;    
    temp = temp->next;
  }
}
void print_list(node *h)
{
  node *temp = h;
  while(temp) {
    printf("\na: %" PRId64 "  c: %" PRId64 "  m:  %" PRId64 "\n", temp->a, temp->c, temp->m);
    temp = temp->next;
  }
}
int list_len(node *h) {
  int len = 0;
  
  while(h) {
    h = h->next;
    len++;
  }

  return(len);
}
/*int main() {
  int64_t a, c, m;
  scanf("%" PRId64, &a);
  scanf("%" PRId64, &c);
  scanf("%" PRId64, &m);

  node * n = init_node(a, c, m);

  while(1) {
  scanf("%" PRId64, &a);
  scanf("%" PRId64, &c);
  scanf("%" PRId64, &m);

    if(a == -1) break;

    add_node(a, c, m, &n);
  }

  print_list(n);
  printf("\n");

  scanf("%" PRId64, &a);
  scanf("%" PRId64, &c);
  scanf("%" PRId64, &m);

  del_node(a, c, m, &n);

  print_list(n);

  clear_list(&n);

  return(0);
}*/