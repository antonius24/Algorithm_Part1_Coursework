#ifndef _Heap_H
#define _Heap_H

struct heap_struct
{
  int capacity;
  int size;
  int *nodes;
};
typedef struct heap_struct *priority_queue;

priority_queue Initialization(int max_elements);
void Update(priority_queue pr_q, long int *length_map, int node);
void Destroy(priority_queue pr_q);
void Insert(priority_queue pr_q, long int *length_map, int node);
int ExtractMin(priority_queue pr_q, long int *length_map);
#endif
