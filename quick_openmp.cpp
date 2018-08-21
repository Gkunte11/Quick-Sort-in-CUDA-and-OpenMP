#include<iostream>
using namespace std;
#include<omp.h>
#include<time.h>
#include<stdlib.h>


int k=0;

int partition(int arr[], int low_index, int high_index)
{
	int i, j, temp, key;		
	key = arr[low_index];
	i= low_index + 1;
	j= high_index;
	while(1)
	{
		while(i < high_index && key >= arr[i])
    			i++;
		while(key < arr[j])
    			j--;
		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			temp= arr[low_index];
			arr[low_index] = arr[j];
			arr[j]= temp;
			return(j);
		}
	}
}


void quicksort(int arr[], int low_index, int high_index)
{
	int j;

	if(low_index < high_index)
	{
		j = partition(arr, low_index, high_index);
		//cout<<"\nPivot element found at index position "<<j;
		//cout<<"\nThread "<<omp_get_thread_num()<<" is running on cpu "<<sched_getcpu()<<"\n";

		#pragma omp parallel sections
		{
    			#pragma omp section
    			{
        			//cout<<"left array :\n";
				//for(int i=low_index;i<=j-1;i++)
				//{
				///	cout<<arr[i]<<"\t";
				//}   
				//cout<<"\n";
        			quicksort(arr, low_index, j - 1);
        
    			}

    			#pragma omp section
    			{
    	 			//cout<<"right array :\n";
				//for(int i=j+1;i<=high_index;i++)
				//{
				//	cout<<arr[i]<<"\t";
				//}   
				//cout<<"\n";
       
        			quicksort(arr, j + 1, high_index);
    			}

		}
	}
}


int main()
{
	int n;
	cout<<"\nEnter the number of elements you want to sort: ";
	cin>>n;
	int a[n];
	time_t t;
	srand((unsigned)time(&t));

	float start, end, total_time_taken;
	
	
	int x,flag;
	for (unsigned i = 0 ; i < n ; i++)
	{
		x=rand()%n;

		flag=0;
		for(int j=0;j<i;j++)
		{
			if(a[j]==x)
			{
				i--;
				flag=1;
				break;
			}
		}
		if(flag==0)
			a[i]=x;
	}
	/*cout<<"\n\n original array\n";
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";*/

	start = omp_get_wtime();

	quicksort(a,0,n-1);
	
	/*cout<<"\n\n after sorting\n";
	for(int i=0;i<n;i++)
		cout<<a[i]<<"\t";
	*/

	//end = clock();
     	total_time_taken = omp_get_wtime() - start;
	cout<<"\n Time taken - \n"<<total_time_taken;
} 

