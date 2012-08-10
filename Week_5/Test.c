#include "Heap.h"
#include <stdlib.h>
#include <stdio.h>
void print_q(priority_queue);
void main()
{
  int i;
  priority_queue pr_q = Initialization(20);
  int *length_map = (int *)malloc(sizeof(int)*10);
  *(length_map+0) = 2;
  *(length_map+1) = 1;
  *(length_map+2) = 3;
  *(length_map+3) = 15;
  *(length_map+4) = 5;
  *(length_map+5) = 12;  
  *(length_map+6) = 7; 
  *(length_map+7) = 11;
  *(length_map+8) = 9;
  *(length_map+9) = 10;
  //printf("%d\n", pr_q->size);
  for (i=0; i< 10; i++)
  {
    Insert(pr_q, length_map, i);
  }
  //printf("test\n");
  print_q(pr_q);  
  *(length_map + 5) = 10;
  Update(pr_q, length_map, 5);
  printf("Update: %d\n", 5);
  print_q(pr_q);
  
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);
  printf("Extract Min: %d\n", ExtractMin(pr_q, length_map));
  print_q(pr_q);

}

void print_q(priority_queue pr_q)
{
  int j=0;
  int k=2;
  int l=1;
  for (j=0; j< (pr_q->size); j++)
  {
    printf("%d ", *(pr_q->nodes + j));
    if (j % 2 == 0)
      printf("  ");
    if (j == 0)
    {
      printf("\n");
    }
    else if ((l%k) == 0)
    {
      printf("\n");
      k*=2;
      l=1;
    }
    else
    {
      l++;
    }
  }
  printf("\n");
}
