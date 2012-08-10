#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Heap.h"


// Input: child index in the tree array
int parent(int child_index)
{
  int parent_index;
  
  if (child_index == 0)
    return -1;  // reach the top of the tree
  else if (child_index % 2 == 1) //odd index
    parent_index = child_index / 2; 
  else //even index
    parent_index = child_index/2 - 1;
  return parent_index;

  
}

priority_queue Initialization(int max_elements)
{
  priority_queue pr_q;
  pr_q = (priority_queue)malloc(sizeof(struct heap_struct));
  pr_q->capacity = max_elements;
  pr_q->size = 0;
  pr_q->nodes = (int *)malloc(sizeof(int) * max_elements);
  *(pr_q->nodes + 0) = 100;
  return pr_q;
}

void Destroy(priority_queue pr_q)
{
  free(pr_q->nodes);
  free(pr_q);
}


void BubbleUp(priority_queue pr_q, long int *length_map, int bubble_node)
{
  int parent_node; //record the parent node
  int child_node; //record the child node
  int child_value; //record the child node length value
  int parent_value; //record the parent node length value
  
  if (parent(bubble_node) == -1)
    return;
  
  parent_node = *(pr_q->nodes + parent(bubble_node));
  //printf("parent_node: %d\n", parent_node);
  child_node = *(pr_q->nodes + bubble_node);
  //printf("child_node: %d\n", child_node);
  parent_value =  *(length_map + parent_node);
  //printf("parent_value: %d\n", parent_value);
  child_value = *(length_map + child_node);
  //printf("child_value: %d\n", child_value);

  if (parent_value > child_value)
  {
    *(pr_q->nodes + parent(bubble_node)) = child_node;
    *(pr_q->nodes + bubble_node) = parent_node;
    BubbleUp(pr_q, length_map, parent(bubble_node));
  }
  return;
}


/*
 *Input: priority_queue
         length_map -- map between node number and its length
         node -- node num
 */
void Insert(priority_queue pr_q, long int *length_map, int node)
{
  int index; //record temporary index
  //printf("test2\n");
  if ((pr_q->size) >= (pr_q->capacity))
  {
    printf("Exceed Maximum Capacity\n");
    exit(1);
  }
  //printf("test3\n");
  *(pr_q->nodes + pr_q->size) = node; 
  //printf("test4\n");
  index = pr_q->size;
  //printf("test5: %d\n", pr_q->size);
  (pr_q->size)++;
  BubbleUp(pr_q, length_map, index);
  return;
}

int child(int bubble_node, int option)
{
  if (option == 0)
    return bubble_node * 2 + 1;
  else
    return bubble_node * 2 + 2;
}

void BubbleDown(priority_queue pr_q, long int *length_map, int bubble_node)
{
  int parent_node;
  int child_node_a;
  int child_node_b;
  int parent_value;
  int child_value_a;
  int child_value_b;
  
  if (bubble_node >= pr_q->size)
  {
    return;
  }
  else if (child(bubble_node, 0) >= pr_q->size)
  {
    return;
  }
  else if (child(bubble_node, 1) >= pr_q->size)
  {
    
    parent_node = *(pr_q->nodes + bubble_node);
    //printf("parent_node: %d\n", parent_node);
    child_node_a = *(pr_q->nodes + child(bubble_node, 0));
    //printf("child_node_a: %d\n", child_node_a);
    parent_value = *(length_map + parent_node);
    child_value_a = *(length_map + child_node_a);
    if (parent_value > child_value_a)
    {    
      *(pr_q->nodes + bubble_node) = child_node_a;
      *(pr_q->nodes + child(bubble_node, 0)) = parent_node;
    }  
    return;
  }
  parent_node = *(pr_q->nodes + bubble_node);
  //printf("parent_node: %d\n", parent_node);
  child_node_a = *(pr_q->nodes + child(bubble_node, 0));
  //printf("child_node_a: %d\n", child_node_a);
  child_node_b = *(pr_q->nodes + child(bubble_node, 1));
  //printf("child_node_b: %d\n", child_node_b);
  parent_value = *(length_map + parent_node);
  child_value_a = *(length_map + child_node_a);
  child_value_b = *(length_map + child_node_b);

  if ((parent_value > child_value_a) && (parent_value > child_value_b))
  {
    if (child_value_a < child_value_b)
    {
      *(pr_q->nodes + bubble_node) = child_node_a;
      *(pr_q->nodes + child(bubble_node, 0)) = parent_node;
      BubbleDown(pr_q, length_map, child(bubble_node, 0));
    } 
    else
    {
      *(pr_q->nodes + bubble_node) = child_node_b;
      *(pr_q->nodes + child(bubble_node, 1)) = parent_node;
      BubbleDown(pr_q, length_map, child(bubble_node, 1));
    }
  }
  else if (parent_value > child_value_a)
  {
      *(pr_q->nodes + bubble_node) = child_node_a;
      *(pr_q->nodes + child(bubble_node, 0)) = parent_node;
      BubbleDown(pr_q, length_map, child(bubble_node, 0));
  }
  else if (parent_value > child_value_b)
  {
      *(pr_q->nodes + bubble_node) = child_node_b;
      *(pr_q->nodes + child(bubble_node, 1)) = parent_node;
      BubbleDown(pr_q, length_map, child(bubble_node, 1));
  }
  else
    return;
}

int ExtractMin(priority_queue pr_q, long int *length_map)
{
  int extract_min;
  extract_min = *(pr_q->nodes + 0);
  pr_q->size--;
  *(pr_q->nodes + 0) = *(pr_q->nodes + pr_q->size);
  BubbleDown(pr_q, length_map, 0);
  return extract_min;

}

void Update(priority_queue pr_q, long int *length_map, int node)
{
  int i=0;
  while (i<(pr_q->size))
  {
    if (*((pr_q->nodes)+i) == node)
      break;
    i++;
  }
  BubbleUp(pr_q, length_map, i);
}
