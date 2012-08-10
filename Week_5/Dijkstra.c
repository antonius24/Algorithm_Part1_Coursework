#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Heap.h"
#include "Dijkstra.h"

#define MAX_NODE 300

linkList *lists; // record the adjacent list
priority_queue unprocessed_heap; //heap for 
int *processed_list; //record whether the vertex is processed. 0-unprocess; 1-process
long int *shortest_path;
int total_num; // totoal node number
int processed_num; // processed node number
//print sub link list
void PrintListRow(int row_index)
{
  listNode *index;
  index = *(lists+row_index);
  while (index != NULL)
  {
    printf("%d | %ld  --->   ", index->node_num, index->length);
    index = index->next;
  }
  printf("\n");
  return;
}


//link list insert node
void InsertNode(int row_index, int node, int length)
{
  listNode *index;
  listNode *pre;
  
  if (*(lists+row_index) == NULL)
  {
    *(lists+row_index) = (listNode *)malloc(sizeof(struct node));
    index = *(lists+row_index);
    index->node_num = node;
    index->length = length;
    index->next = NULL;
  }
  else
  {
    index = *(lists+row_index);
    pre = *(lists+row_index);
    while (index != NULL)
    {
      pre = index;
      index = index->next;
    }
    index = (listNode *)malloc(sizeof(struct node));
    index->node_num = node;
    index->length = length;
    index->next = NULL;
    if (pre != NULL)
    {
      pre->next = index;
    }
  }
  return;
}

long int SearchNode(int vertex_index, int node_num_index)
{
  linkList index = *(lists+vertex_index);
  if (index == NULL)
    return 1000000;
  while (1)
  {
    if (index->node_num == (node_num_index+1))
      return index->length;
    if (index->next == NULL)
      break;
    index = index->next;
  }
  return 1000000;
}


void ReadGraphFile()
{
  int length;
  int row_index;
  char buf[300];
  char **bufs;
  char *num_string;
  char *num_node;
  char *num_length;
  FILE *fp;
  
  bufs = (char **)malloc(sizeof(char *) * MAX_NODE);
  if ((fp = fopen("dijkstraData.txt", "r")) == NULL)
  {
    printf("File error!\n");
    exit(1);
  }


  while (fgets(buf, 300, fp) != NULL)
  {
    int bufs_index = 0;
    length = strlen(buf);
    //printf("length-1: %c\n", buf[length-1]);
    buf[length-2] = '\0';
    num_string = strtok(buf,"	");
    row_index = atoi(num_string)-1;
    total_num = row_index+1;
    num_string = strtok(NULL, "	");
    while(num_string != NULL)
    {
      *(bufs+bufs_index) = (char *)malloc(sizeof(char) * 30);
      *(bufs+bufs_index) = num_string;
      bufs_index++;
      num_string = strtok(NULL, "	");   
    }
    int i;
     
    for (i=0; i<bufs_index; i++)
    {
      num_node = strtok(*(bufs+i),",");
      num_length = strtok(NULL, "	");
      InsertNode(row_index, atoi(num_node), atoi(num_length));
    }
    printf("Row %d: ", row_index);
    PrintListRow(row_index);
  }
}


void UpdateHeap(int recent_processed_index)
{
  int temp;
  int new_path;
  linkList index = *(lists+recent_processed_index);
  while(1)
  {
    temp = (index->node_num)-1;
    if (*(processed_list+temp) == 0) //unprocessed 
    {
      new_path = *(shortest_path+recent_processed_index) + index->length; // A[w] + lwv
      if (*(shortest_path+temp) > new_path)
      {
        *(shortest_path+temp) = new_path;
        Update(unprocessed_heap, shortest_path, temp);
      }
    }
    if (index->next == NULL)
      break;
    index = index->next;
  }
  return;
}


void DijkstraShort()
{
  //start node
  int recent_processed; // recent processed node
  int i;
  *(processed_list+0) = 1; //start node
  *(shortest_path+0) = 0; //start node
  recent_processed = 0;
  for (i=1; i<total_num; i++)  //add all unprocessed number into heap
  {
    Insert(unprocessed_heap, shortest_path, i);
  }
  int min_vertex;
  while (processed_num <= total_num)
  {
    UpdateHeap(recent_processed);
    processed_num++;

    min_vertex = ExtractMin(unprocessed_heap, shortest_path);
    *(processed_list+min_vertex) = 1;
    recent_processed = min_vertex;
  }
  return;
}

int main()
{
  lists = (linkList *)malloc(sizeof(linkList) * MAX_NODE);
  ReadGraphFile();
  //printf("total_num: %d\n", total_num);
  processed_list = (int *)malloc(sizeof(int) * total_num);
  shortest_path = (long int *)malloc(sizeof(long int) * total_num);
  unprocessed_heap = Initialization(total_num);
  processed_num = 0;
  int i;

  for(i=0; i<total_num; i++)
  {
    *(processed_list+i) = 0;
    *(shortest_path+i) = 1000000;
  }

  DijkstraShort();
  
  for (i=0; i<total_num; i++)
  {
    if ((i==6)||(i==36)||(i==58)||(i==81)||(i==98)||(i==114)||(i==132)||(i==164)||(i==187)||(i==196))
    printf("shortest_path %d: %ld\n", i+1, *(shortest_path+i));
  }


  return 0;
}


