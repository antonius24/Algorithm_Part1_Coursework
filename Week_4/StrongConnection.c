#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define ROW_NODES_ALLOC 400

long int **graph_list; // graph adjacent list
long int **graph_list_rev; // reversed graph adjacent list
long int **graph_list_finish; //graph adjacent list by finish time
long int nodes_num = 0;
int *explore_status;
long int *end_index; // record the end index of each row
long int *end_index_rev; // record the end index of each reversed row
long int *finish_time;
long int *leader;
long int *SCC_num;
long int finish_time_cur = 0; // record current finish time
long int leader_cur = 0;

void FreeMemory()
{
  int i, j;
  i=0;
  while (i < nodes_num)
  {
    if (*(graph_list+i) != NULL)
      free(*(graph_list+i));
    if (*(graph_list_rev+i) != NULL)
      free(*(graph_list_rev+i));
    //if (*(graph_list_finish+i) != NULL)
    //  free(*(graph_list_finish+i));
    i++;
  }
  //free(leader);
  //free(explore_status);
  //free(finish_time);
  //free(SCC_num);
  free(graph_list);
  free(graph_list_rev);
}
void PrintGraphFinish()
{
  FILE *graph;
  long int i,j;
  i=0;
  j=0;
  if ((graph = fopen("graph_finish.txt", "w")) == NULL)
  {
    printf("File Error\n");
    exit(1);
  }
  while(1)
  {
    if(*(graph_list_finish+i) != NULL)
    {
      j=0;
      fprintf(graph, "%ld ", i+1);
      while (*(*(graph_list_finish+i)+j) != NULL)
      {
        //printf("%d ", *(*(graph_list+i)+j));
        fprintf(graph, "%ld ", *(*(graph_list_finish+i)+j));
        j++;
      }
      //printf("\n");
      fprintf(graph, "\n");      
    }
    i++;
    if (i > (nodes_num-1))
      break;
  }
}

void PrintGraph()
{
  FILE *graph;
  long int i,j;
  i=0;
  j=0;
  printf("nodes_num: %ld\n", nodes_num);
  if ((graph = fopen("graph.txt", "w")) == NULL)
  {
    printf("File Error\n");
    exit(1);
  }
  while(1)
  {
    if(*(graph_list+i) != NULL)
    {
      j=0;
      fprintf(graph, "%ld ", i+1);
      while (*(*(graph_list+i)+j) != NULL)
      {
        //printf("%d ", *(*(graph_list+i)+j));
        fprintf(graph, "%ld ", *(*(graph_list+i)+j));
        j++;
      }
      //printf("\n");
      fprintf(graph, "\n");      
    }
    i++;
    if (i > (nodes_num-1))
      break;
  }
}

void PrintReverseGraph()
{
  FILE *graph_rev;
  long int i,j;
  i=0;
  j=0;

  if ((graph_rev = fopen("graph_rev.txt", "w")) == NULL)
  {
    printf("File Error\n");
    exit(1);
  }
  while (1)
  {
    if (*(graph_list_rev+i) != NULL)
    {
      j=0;
      fprintf(graph_rev, "%ld ", i+1);
      while (*(*(graph_list_rev+i)+j) != NULL)
      {
        //printf("%d ", *(*(graph_list+i)+j));
        fprintf(graph_rev, "%ld ", *(*(graph_list_rev+i)+j));
        j++;
      }
      //printf("\n");
      fprintf(graph_rev, "\n");
    }
    i++;
    if (i > nodes_num)
      break;
  }
}


void ReadGraphFile()
{
  char buf[50];
  FILE *temp;
  FILE *fp;
  int length;
  long int index=0;
  //int last_tail = -1; // recorde whether the tail is changed, used to reset row_nodes_alloc_flag and row_nodes_alloc_flag_rev
  //int row_nodes_alloc_flag = 0; // indicate when to realloc the row memory
  //int row_nodes_alloc_flag_rev = 0;
  char *number;
  long int tail;
  long int head;
  
  if ((fp = fopen("SCC.txt", "r")) == NULL)
  {
    printf("File Error!\n");
    exit(1);
  }
  /*
  if ((temp = fopen("result.txt", "w")) == NULL)
  {
    printf("File Error!\n");
    exit(1);
  }
  */
  
  while (fgets(buf, 50, fp) != NULL)
  {
    index++;
    length = strlen(buf);
    buf[length-1] = '\0';
    number = strtok(buf, " ");
    tail = atoi(number);
    number = strtok(NULL, " ");
    head = atoi(number);

    // record the node num
    if (nodes_num < head)
    {
      nodes_num = head;
    }
    if (nodes_num < tail)
    {
      nodes_num = tail;
    }

    //Record origin graph in adjacent list
    if (*(graph_list+tail-1) == NULL)
    {
      //printf("malloc tail: %ld\n", tail);
      *(graph_list+tail-1) = (long int *)malloc(sizeof(long int) * ROW_NODES_ALLOC);
      *(end_index+tail-1) = 0;
    }
    /*
    index = 0;
    while (*(*(graph_list+tail-1)+index) != NULL)
    {
      index++;
    }
    */
    *(*(graph_list+tail-1)+*(end_index+tail-1)) = head;
    (*(end_index+tail-1))++;
    //printf("tail: %d head: %d\n", tail, *(*(graph_list+tail-1)+index));
    
    
    
    
    // Record reverse graph in adjacent list
    if (*(graph_list_rev+head-1) == NULL)
    {
      //printf("rev: malloc tail: %d\n", head);
      *(graph_list_rev+head-1) = (long int *)malloc(sizeof(long int) * ROW_NODES_ALLOC);
      *(end_index_rev+head-1) = 0;
    }
    /*
    index = 0;
    while (*(*(graph_list_rev+head-1)+index) != NULL)
    {
      //printf("%d\n", *(*(graph_list_rev+head-1)+index));
      index++;
    }
    */
    *(*(graph_list_rev+head-1)+*(end_index_rev+head-1)) = tail;
    (*(end_index_rev+head-1))++;
    //printf("rev: head: %d tail: %d\n", tail, *(*(graph_list_rev+head-1)+index));
    //fprintf(temp, "tail: %d\n", tail);
    //fprintf(temp, "head: %d\n", head);
    //fprintf(temp, "\n");
    if ((index % 100000) == 0)
      printf("index: %ld\n", index/100000);
  }
  PrintGraph();
  PrintReverseGraph();
  fclose(fp);
  //fclose(temp); 
}


int DFS(int option, long int start_vertex)
{
  long int i;

  printf("in DFS\n");
  *(explore_status+start_vertex-1) = 1;
  if (option == 0) // if option=0, start_vertex is in original list order
  {
    //current_vertex = *(finish_time+start_vertex-1);
    i=0;
    *(leader+start_vertex-1) = leader_cur;
    while (*(*(graph_list+start_vertex-1)+i) != NULL)
    {
      long int next_node = *(*(graph_list+start_vertex-1)+i);
      printf("next node: %ld\n", next_node);
      if (*(explore_status + next_node-1) == 0) // finish list
      {  
        printf("unexplored node\n");
        DFS(0, next_node);
      }
      i++;
    }
  }
  else //reversed list
  {
    i=0;
    while (*(*(graph_list_rev+start_vertex-1)+i) != NULL)
    {
      long int next_node = *(*(graph_list_rev+start_vertex-1)+i);
      printf("next node: %ld\n", next_node);
      if(*(explore_status + next_node-1) == 0) // original list
      {  
        printf("unexplored node\n");
        DFS(1, next_node);
      }
      i++;
    }
    finish_time_cur++;
    *(finish_time + start_vertex-1) = finish_time_cur;
    printf("start_vertex %ld finish time: %ld\n", start_vertex, finish_time_cur);
  }
  return 0;
}

void DFS_Loop(int option)
{
  printf("in DFS_Loop\n");
  finish_time_cur = 0;
  leader_cur = 0;
  long int i,j;
  if (option == 0) // original list
  {
    for (i=nodes_num; i>0; i--)//i == finish_time
    {
      j=0;
      while (1)
      {
        if (i == *(finish_time+j))
          break;
        j++;
      }
      if (*(explore_status+j) == 0)
      {  
        leader_cur = j+1;
        printf("next_node_loop: %ld\n", j+1);
        DFS(0,j+1);
      }
    }
  }
  else // reversed list
  {
    for (i=nodes_num; i>0; i--)
    {
      printf("i: %ld\n", i);
      if(*(explore_status+i-1) == 0)
      {
        leader_cur = i;
        DFS(1, i);
      }
    }
  }
}

void SCC_Print()
{
  long int find_num = 5;
  long int i;
  long int max = 0;
  long int max_node = 0;
  i=0;
  while (i<nodes_num)
  {
   (*(SCC_num + (*(leader+i)-1)))++;
   i++;
  }
  i=0;
  while (i<nodes_num)
  {
    printf("node %ld SCC_num: %ld\n", i+1, *(SCC_num+i));
    i++;
  }
  i=0;
  while(find_num > 0)
  {
    i=0;
    max = 0;
    max_node = 0;
    while (i<nodes_num)
    {
      if (*(SCC_num+i) > max)
      {
        max = *(SCC_num+i);
        max_node = i+1;
      }
      i++;
    }
    printf("%ld Max SCC: %ld\n", 6-find_num, max);
    (*(SCC_num+max_node-1)) = 0;
    find_num--;
  }
}

void CreateFinishList() // create finish_list according to graph_list
{
  long int i, j, next_finish;
  
  for (i=0; i<nodes_num; i++)
  { 
    next_finish = *(finish_time+i) - 1;
    printf("next_finish: %ld\n", next_finish);
    *(graph_list_finish+next_finish) = *(graph_list+i);
  }
}

int main()
{
  graph_list = (long int **)malloc(sizeof(long int *)*1000000);
  graph_list_rev = (long int **)malloc(sizeof(long int *)*1000000);
  graph_list_finish = (long int **)malloc(sizeof(long int *)*1000000);
  end_index = (long int *)malloc(sizeof(long int)*1000000);
  end_index_rev = (long int *)malloc(sizeof(long int)*1000000);
  ReadGraphFile();
  explore_status = (int *)calloc(nodes_num, sizeof(int));
  finish_time = (long int *)calloc(nodes_num, sizeof(long int));
  leader = (long int *)calloc(nodes_num, sizeof(long int));
  SCC_num = (long int *)calloc(nodes_num, sizeof(long int));
  DFS_Loop(1);
  printf("END LOOP 1\n\n");
  explore_status = (int *)calloc(nodes_num, sizeof(int));
  DFS_Loop(0);
  printf("END LOOP 2\n");
  SCC_Print();
  //CreateFinishList();
  
  long int i;
  printf("\n");
  for (i=0; i<nodes_num; i++)
  {
    printf("vertex %ld finish time: %ld\n", i+1, *(finish_time+i));
  }
  //PrintGraphFinish();
  for (i=0; i<nodes_num; i++)
  {
    printf("vertex %ld leader: %ld\n", i+1, *(leader+i));
  }
  /*
  int i=0;
  printf("here\n");
  while (1)
  {
    if (*(explore_status+i) == NULL)
    {
      printf("NULL\n");
    }
    *(explore_status+i) = 1;
    if (*(explore_status+i) == NULL)
    {
      printf("NULL2\n");
    }
    printf("%d\n", *(explore_status+i));
    i++;
    if (i >= nodes_num)
      break;
  }
  */
  FreeMemory();

}
