#include<iostream>
#include<cstdlib>

using namespace std;

void quickSort(int array[], int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = array[(left + right) / 2];

	// partition
	while(i <= j)
	{
		while(array[i] < pivot)
		{
			i++;
		}
		while(array[j] > pivot)
		{
			j--;
		}
		if(i <= j)
		{
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}

	// recursion
	if(left < j)
	{
		quickSort(array, left, j);
	}
	if(i < right)
	{
		quickSort(array, i, right);
	}
}

int main()
{
	int a[] = {12,10,43,23,-78,45,123,56,98,41,90,24};
	int num = sizeof(a)/sizeof(int);

	quickSort(a,0,num-1);

	for(int i=0; i<num; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}
