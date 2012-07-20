#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

FILE *fp_temp;

typedef struct count
{
	int *array;
	long long int invertion_num;
}count_struct;

count_struct Sort_Count(int *array, int length)
{
	int *first_half;
	int *second_half;
	//int *sorted_array;
	int i;	
	int index=0;
	int first_length=0;	
	int second_length=0;
	count_struct sorted_ct_struct_first;
	count_struct sorted_ct_struct_second;
	count_struct sorted_ct_struct_array;
	first_half = (int *)malloc(sizeof(int)*((length/2)+1));
	second_half = (int *)malloc(sizeof(int)*((length/2)+1));
	sorted_ct_struct_array.array = (int *)malloc(sizeof(int)*length);
	sorted_ct_struct_array.invertion_num = 0;	
	//printf("1\n");
	if (length == 1)
	{
		//fprintf(fp_temp,"a: %d\n", *(array));
		count_struct temp_struct;
		temp_struct.array = array;
		temp_struct.invertion_num = 0;
		return temp_struct;
	}	
	if (length == 2)
	{
		count_struct temp_struct;
		temp_struct.invertion_num = 0;
		
		int temp;
		if (*array > *(array+1))
		{
			temp = *array;
			*array = *(array+1);
			*(array+1) = temp;
			temp_struct.invertion_num = 1;
			//printf("%d\n", *(array));
			//printf("%d\n", *(array+1));
			//fprintf(fp_temp,"b: %d\n", *(array));
			//fprintf(fp_temp,"c: %d\n", *(array+1));
		}
		temp_struct.array = array;
		return temp_struct;
	}
	else
	{
		//printf("2\n");
		for (i=0; i<length/2; i++)
		{
			*(first_half+index) = *(array+i);
			index++;
		}
		first_length = index;
		*(first_half+index) = '\0';
		index=0;
		for (i=length/2; i<length; i++)
		{
			*(second_half+index) = *(array+i);
			index++;
		}	
		*(second_half+index) = '\0';
		second_length = index;
		
		//printf("3\n");
		//int *sorted_first_half;
		//int *sorted_second_half;

		sorted_ct_struct_first.array = (int *)malloc(sizeof(int)*(first_length));
		sorted_ct_struct_second.array = (int *)malloc(sizeof(int)*(second_length));
		sorted_ct_struct_first = Sort_Count(first_half, first_length);
		sorted_ct_struct_second = Sort_Count(second_half, second_length);
		int j=0; 
		int k=0;
		for (i=0; i<length; i++)  // merge
		{
			if ((j<first_length) && (k<second_length))
			{
			if (*(sorted_ct_struct_first.array+j) < *(sorted_ct_struct_second.array+k))
			{
				*(sorted_ct_struct_array.array+i) = *(sorted_ct_struct_first.array+j);
				j++;
			}	
			else
			{
				*(sorted_ct_struct_array.array+i) = *(sorted_ct_struct_second.array+k);
				sorted_ct_struct_array.invertion_num += first_length - j;
				k++;
			}
			}
			else if (j>=first_length)
			{
				*(sorted_ct_struct_array.array+i) = *(sorted_ct_struct_second.array+k);
				k++;							
			}
			else
			{
				*(sorted_ct_struct_array.array+i) = *(sorted_ct_struct_first.array+j);
				j++;				
			}
		}	
		//printf("4\n");
		sorted_ct_struct_array.invertion_num += sorted_ct_struct_first.invertion_num;
		sorted_ct_struct_array.invertion_num += sorted_ct_struct_second.invertion_num;
		return sorted_ct_struct_array;
	}
}


int main()
{
	//static FILE *fp_temp;
	FILE *fp;
	int length;
	char buf[256];
	int buf_int;
	int *bufs;
	//int *sorted_bufs;
	count_struct sorted_ct_struct_bufs;
	int index=0;
	bufs = (int *)malloc(sizeof(int)*200000);
	sorted_ct_struct_bufs.array = (int *)malloc(sizeof(int)*200000);
	if ((fp = fopen("IntegerArray.txt", "r"))== NULL)
	{
		printf("Cannot open the file!\n");
		exit(1);
	}	
	if ((fp_temp=fopen("result.txt","w")) == NULL)
	{
		printf("error\n");
		exit(1);
	}	
	//fprintf(fp_temp,"2");
	//printf("a\n");
	while (fgets(buf, 256, fp) != NULL)
	{

		length = strlen(buf);
		buf[length-1] = '\0';
		buf_int = atoi(buf);
		//printf("%d\n", index);
		*(bufs+index) = buf_int;
		index++;
		//printf("%d\n", 9/2);
		//printf(":%d\n",buf_int);
	}
	//printf("b\n");
	sorted_ct_struct_bufs = Sort_Count(bufs, index);
	int i;	
	for (i=0; i<index; i++)
	{
		fprintf(fp_temp,"%d\n",*(sorted_ct_struct_bufs.array+i));
	}
	printf("final: %lld\n",sorted_ct_struct_bufs.invertion_num);
	
	return 0;
}
