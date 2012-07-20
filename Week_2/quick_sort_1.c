#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int compare_num = 0;
int main()
{
	FILE *fp;
	FILE *rp;
	char buf[256];
	int buf_int;	
	int *bufs;
	int index = 0;
	int length;
	int option = 1; // 1 - choose leftmost as pivot
			// 2 - choose rightmost as pivot
			// 3 - choose median-of-three as pivot
	
	bufs = (int *)malloc(sizeof(int)*20000);
	if ((fp = fopen("QuickSort.txt","r")) == NULL)
	{
		printf("File Error!\n");
		exit(1);
	}
	if ((rp = fopen("Result.txt", "w")) == NULL)
	{
		printf("File Error!\n");
		exit(1);
	}

	while (fgets(buf, 256, fp) != NULL)
	{
		length = strlen(buf);
		buf[length-1] = '\0';  //get rid of return 
		buf_int = atoi(buf);
		*(bufs+index) = buf_int;
		index++;
		//printf("test\n");
	}

	int i;
	//for (i=0; i<index; i++)
	//{
	//	printf("%d\n",*(bufs+i));
	//}
	QuickSort(bufs, 0, index-1, option);
		
	for (i=0; i<index; i++)
	{
		fprintf(rp, "%d\n",*(bufs+i));
	}
	printf("Option: %d\n", option);
	printf("Compare Number: %d\n", compare_num);
	return 0;
}

int Partition(int *bufs, int left_pos, int right_pos)
{
	int pivot;
	int i; // boundary between <pivot and >pivot
	int j; // boundary between partitioned and unpartitioned
	int temp;	
	//printf("partition");
	pivot = *(bufs+left_pos);
	i = left_pos+1;
	for (j=left_pos+1; j<=right_pos; j++)
	{
		if (*(bufs+j) < pivot)
		{
			if (j == i)  //no need to swap
			{
				i++;
			}
			else
			{
				temp = *(bufs+i);
				*(bufs+i) = *(bufs+j);
				*(bufs+j) = temp;
				i++;
			}	
		}
	}
	if ((i-1) == left_pos)  // no item < pivot, no need to swap
	{
		return left_pos;
	}
	temp = *(bufs+left_pos);
	*(bufs+left_pos) = *(bufs+i-1);
	*(bufs+i-1) = temp;
	return i-1;
	
}

QuickSort(int *bufs, int left_pos, int right_pos, int option)
{
	int pivot_pos;
	if (option == 1)		//leftmost
	{
		compare_num += (right_pos - left_pos);
		pivot_pos = Partition(bufs, left_pos, right_pos);
		if ((left_pos != pivot_pos-1) && (left_pos != pivot_pos))  // if pivot is the leftmost or the second of leftmost, no need to swap
		{
			QuickSort(bufs, left_pos, pivot_pos-1, 1);
		}
		if (((pivot_pos+1) != right_pos) && (pivot_pos != right_pos)) // if pivot is the rightmost or the second of rightmost, no need to swap
		{		
			QuickSort(bufs, pivot_pos+1, right_pos, 1);
		}	
	}
	else if (option == 2)		// rightmost
	{
		int temp;
		compare_num += (right_pos - left_pos);
		
		temp = *(bufs+right_pos);
		*(bufs+right_pos) = *(bufs+left_pos);
		*(bufs+left_pos) = temp;
		pivot_pos = Partition(bufs, left_pos, right_pos);
		if ((left_pos != pivot_pos-1) && (left_pos != pivot_pos))  // if pivot is the leftmost or the second of leftmost, no need to swap
		{
			QuickSort(bufs, left_pos, pivot_pos-1, 2);
		}
		if (((pivot_pos+1) != right_pos) && (pivot_pos != right_pos)) // if pivot is the rightmost or the second of rightmost, no need to swap
		{		
			QuickSort(bufs, pivot_pos+1, right_pos, 2);
		}
	}
	else		// median of the three
	{
		int temp;
		int *median;
		median = (int *)malloc(sizeof(int)*3);
		compare_num += (right_pos - left_pos);
		if ((right_pos - left_pos) >= 2)		// if <2, leftmost will be the pivot as defined
		{
			*(median+0) = *(bufs+left_pos);
			*(median+1) = *(bufs + left_pos +(right_pos-left_pos)/2);
			*(median+2) = *(bufs+right_pos);
			int l;		
			int k;
			//for (l=0; l<3; l++)
			//{
			//	printf("before:%d: %d\n", l, *(median+l));
			//}
			for (k=2; k>0; k--)
			{
				int j;
				for (j=0;j<k;j++)
				{
					if (*(median+j) > *(median+j+1))
					{
						int temp;
						temp = *(median+j);
						*(median+j) = *(median+j+1);
						*(median+j+1) = temp;
					}
				}
			}
			//for (l=0; l<3; l++)
			//{
			//	printf("after:%d: %d\n", l, *(median+l));
			//}	
			if (*(median+1) == (*(bufs+right_pos)))
			{
				temp = *(bufs+right_pos);
				*(bufs+right_pos) = *(bufs+left_pos);
				*(bufs+left_pos) = temp;				
			}
			else if (*(median+1) == (*(bufs + left_pos +(right_pos-left_pos)/2)))
			{
				temp = *(bufs + left_pos +(right_pos-left_pos)/2);
				*(bufs + left_pos +(right_pos-left_pos)/2) = *(bufs+left_pos);
				*(bufs+left_pos) = temp;				
			}	
		}		
		pivot_pos = Partition(bufs, left_pos, right_pos);
		if ((left_pos != pivot_pos-1) && (left_pos != pivot_pos))  // if pivot is the leftmost or the second of leftmost, no need to swap
		{
			QuickSort(bufs, left_pos, pivot_pos-1, 3);
		}
		if (((pivot_pos+1) != right_pos) && (pivot_pos != right_pos)) // if pivot is the rightmost or the second of rightmost, no need to swap
		{		
			QuickSort(bufs, pivot_pos+1, right_pos, 3);
		}
		free(median);	
	}
}	
