#ifndef _DIJK_H
#define _DIJK_H

typedef struct node
{
  int node_num;
  long int length;
  struct node *next;
}listNode, *linkList;

#endif
