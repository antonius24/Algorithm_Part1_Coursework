#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#define INT_MAX 30000
//FILE *result;
int main()
{
  long int run_times;
  int min_cut=INT_MAX;
  int min_cut_temp;
  run_times = 1;
  
  while (run_times >= 0)
  {
    min_cut_temp = RandomContraction();
    if (min_cut_temp < min_cut)
      min_cut = min_cut_temp;
    run_times--;
  }
  printf("Final Min Cut: %d\n", min_cut);
  return 0;
}

int RandomContraction()
{
  FILE *fp;
  
  char buf[256];
  int length;
  char *num;
  int **bufs;
  int **bufs_2;
  int *bufs_row;
  int buf_int;
  int vertices_num;
  int index = 0;
  int row_index = 0;
  int edges_num=0;
  int min_cut= INT_MAX;
  int min_cut_temp;
  FILE *temp_fp;
  FILE *temp_result;
  //int *vertices_edge_num; // record how many edges does each vertex have

  //*temp_fp = *fp;
  //*temp_result = *result;
  bufs = (int **)malloc(sizeof(int)*200000);
  //bufs_2 = (int **)malloc(sizeof(int)*100000);
  if ((fp = fopen("kargerMinCut.txt","r")) == NULL)
	{
		printf("File Error!\n");
		exit(1);
	}
	/*
	if ((result = fopen("result.txt", "w")) == NULL)
	{
	  printf("File Error!\n");
	  exit(1);
	}
	*/
  while (fgets(buf, 256, fp)!= NULL)
  {
    length = strlen(buf);
    buf[length-1] = '\0';
    num = strtok(buf, "	");
    row_index = atoi(num)-1;
    num = strtok(NULL, "	");
    bufs_row = (int *)malloc(sizeof(int)*4000);
    while(num != NULL)
    {  
      buf_int = atoi(num);
      if (buf_int > 0)
      {
        *(bufs_row+index) = buf_int;
        index++;
      }
      num = strtok(NULL, "	");
    }
    *(bufs+row_index) = bufs_row;
    vertices_num = row_index+1;
    index = 0;
  }
  //printf("test1\n");
  
  //vertices_edge_num = (int *)malloc(sizeof(int)*vertices_num);
  
  int i=0;
  int j=0;
  while (*(bufs+i) != NULL)
  {
    while(*(*(bufs+i)+j) != NULL)
    {
      //printf("bufs: %d\n", *(*(bufs+i)+j));
      j++;
    }
    //*(vertices_edge_num + i) = j;
    edges_num = edges_num + j;
    //printf("j:: %d\n", j);
    //printf("i:: %d\n", i);
    //printf("edges_num:: %d\n", edges_num);
    i++;
    j=0;
  }
  //printf("edges_num: %d\n", edges_num);
  
  int run_times = vertices_num * vertices_num;
  
  /*
  i=0;
  j=0;
  while (*(bufs+i) != NULL)
  {
    while (*(*(bufs+i)+j) != NULL)
    {
      printf("here_2\n");
      *(*(bufs_2+i)+j) = *(*(bufs+i)+j);
      j++;
    }
    i++;
  }
  printf("here\n");
  */
  min_cut = RContraction(bufs, vertices_num, 0);
  //printf("Min-Cut: %d\n", min_cut); 
  fclose(fp);
  //fclose(result);
  return min_cut;
}

int RContraction(int **bufs, int vertices_num, int removed_vertices)
{
  int random;
  int random_col;
  int erased_vertex;
  int merge_vertex;
  int cut_num=0;
  int i=0;
  int j=0;
  int k=0;
  int is_found=0;
  long int edges_num=0;
  
  if (vertices_num - removed_vertices <= 2)
  {
    //printf("for test 1\n");
    while (*(bufs+i) != NULL)
    {
        j=0;
        while(*(*(bufs+i)+j) != NULL)
        {
          if(*(*(bufs+i)+j) != -1)
            cut_num++;
          //printf("cut_num: %d\n", cut_num);
          //printf("value: %d\n", *(*(bufs+i)+j));
          j++;
        }
        i++;
    }
    return cut_num/2;   
  }
  else
  {
    i=0;
    j=0;
    edges_num=0;
    while (*(bufs+i) != NULL)
    {
      //fprintf(result, "line: %d\n", i+1);
      while(*(*(bufs+i)+j) != NULL)
      {
        if (*(*(bufs+i)+j) != -1)
        {
          //fprintf(result, "bufs_value: %d\n", *(*(bufs+i)+j));
          //fprintf(result, "edges_num: %d\n", edges_num);
          edges_num++;
        }
        j++;
      }
      //fprintf(result, "edges_num: %d\n", edges_num);
      //fprintf(result, "\n");
      i++;
      j=0;
    }  
  
  
    // Randomly choose an edge
    //printf("for test 2, edges_num = %d\n", edges_num);
    while (1)
    {
      srand(time(0));
      random = (int)(rand()%edges_num);
      //printf("random: %d\n", random);
      i=0;
      j=0;
      while (*(bufs+i) != NULL)
      {
        while(*(*(bufs+i)+j) != NULL)
        {
          if (*(*(bufs+i)+j) != -1)
          {
            if (random == 0)
            {
              erased_vertex = *(*(bufs+i)+j);
              merge_vertex = i+1;
              //printf("erased_j = %d\n", j);
              //fprintf(result, "erased_vertex = %d\n", erased_vertex);
              //fprintf(result, "merge_vertex = %d\n", merge_vertex);
              is_found = 1;
              break; 
            }
            else
            {
              //printf("random--\n");
              random--;
            }
          }
          j++;
        }
        if (is_found)
          break;
        i++;
        j=0;
      }
      if (is_found)
      {
        is_found = 0;
        break;
      }
    }
      // merge the two vertices && remove self-loop
    i=0;
    k=0;
    j=merge_vertex-1;
    int merge_index=0;
    while (*(*(bufs+j)+merge_index) != NULL)
    {
      merge_index++;
    }
    while (*(bufs+i) != NULL)
    {
      //printf("A\n");
      while(*(*(bufs+i)+k) != NULL)
      {
        if (i == merge_vertex-1)  // merge vertex should be considered separatedly
        {
          if (*(*(bufs+i)+k) == erased_vertex)
          {
            *(*(bufs+i)+k) = -1;
          } 
        }
        else if (i == erased_vertex-1) // rip out the erased_vertex
        {
           if (*(*(bufs+i)+k) != merge_vertex)  // if the scanned vertex == merge vertex, means there is self-loop, just erase it 
           {
             *(*(bufs+j)+merge_index) = *(*(bufs+i)+k);
             merge_index++;
             //printf("merge_index: %d\n", merge_index);
           }
             *(*(bufs+i)+k) = -1;
        }
        else
        {
          if(*(*(bufs+i)+k) == erased_vertex) //redirect other edges
          {
            (*(*(bufs+i)+k)) = merge_vertex;  
          }
        }
        k++;
      } 
      k=0;
      i++;
    }
    removed_vertices++;
    //printf("B\n");
  i=0;
  j=0;
  while (*(bufs+i) != NULL)
  {
    j=0;
    while(*(*(bufs+i)+j) != NULL)
    {
      //fprintf(result, "%d\n", *(*(bufs+i)+j));
      j++;
    }
    //fprintf(result, "\n");
    i++;
  }
    return RContraction(bufs, vertices_num, removed_vertices); 
    }
    return 0;
}
