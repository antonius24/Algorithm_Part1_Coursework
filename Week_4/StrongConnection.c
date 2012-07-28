#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int **graph_list; // graph adjacent list
int **graph_list_rev; // reversed graph adjacent list

int main()
{
  graph_list = (int **)malloc(sizeof(int)*100000);
  graph_list_rev = (int **)malloc(sizeof(int)*100000);
  ReadGraphFile()
}

void ReadGraphFile()
{
  char buf[50];
  FILE *fp;
  int length;
  
  if ((fp = fopen("SCC.txt", "r")) == NULL)
  {
    printf("File Error!\n");
    exit(1);
  }
  
  while (fgets(buf, 50, fp) != NULL)
  {
    length = strlen(buf);
    buf[length-1] = '\0';
  } 
}
