#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int * x, int * y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void heapify(int arr[], int n, int i) {
	int Lrg = i;
	int l = (2*i) + 1;
	int r = (2*i) + 2;
	if(l < n && arr[l] > arr[Lrg]) {
		Lrg = l;
	}
	if(r < n && arr[r] > arr[Lrg]) {
		Lrg = r;
	}
	// Swap and continue heapifying if root is not largest
	if(Lrg != i) {
		swap(&arr[i], &arr[Lrg]);
		heapify(arr, n, Lrg);
	}
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	for(int i = n; ((i/2)-1) < 0; i--) {
		heapify(arr, n, i);
	}
	for(int i = n-1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r) {
		int m = ((l + r) / 2);
		mergeSort(pData, m+1, r);
		mergeSort(pData, l, m);

		int sizeL = m - l + 1;
		int sizeR = r - m;

		int * tempL = (int *)malloc(sizeof(int) * sizeL);
		for(int i = 0; i < (m-l+1); ++i) {
			tempL[i] = pData[l + i];
		}

		int * tempR = (int *)malloc(sizeof(int) * sizeR);
		for(int i = 0; i < (r - m); ++i) {
			tempR[i] = pData[m + i + 1];
		}

		int iL = 0;
		int iR = 0;
		int k = l;
		while(iL < sizeL && iR < sizeR) {
			if(tempL[iL] <= tempR[iR]) {
				pData[k] = tempL[iL];
				++iL;
			}
			else {
				pData[k] = tempR[iR];
				++iR;
			}
			++k;
		}
	
		while(iL < sizeL) {
			pData[k] = tempL[iL];
			++iL;
			++k;
		}
		while(iR < sizeR) {
			pData[k] = tempR[iR];
			++iR;
			++k;
		}
		free(tempL);
		free(tempR);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
/*
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}
*/

void printArray(int pData[], int dataSz) {
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	if(dataSz < 100) {
		for (i = 0; i < dataSz; ++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n");
	}
	else {
		for (i=0;i<100;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
	
		for (i=sz;i<dataSz;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\n");
	}
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}