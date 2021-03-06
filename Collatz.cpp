
//#include "stdafx.h"
#pragma warning(disable:4996)
#include<climits>
#include<iostream>
using namespace std;

typedef struct Elem
{
	int indexMax;
	int indexMin;
	int indexArr;
	unsigned int number;
	char check;

}Element;

void swap(int &x, int &y)
{
	int tmp;
	tmp = x;
	x = y;
	y = tmp;
}


int parent(int i)
{
	return i / 2;
}

int left(int i) {
	return i * 2;
}

int right(int i) {
	return i * 2 + 1;
}

	void minHeapify(Element *heap,Element* maxHeap, int index, int heapSize)
	{
		int largest = index;
		Element tmp;
		int l = left(index);
		int r = right(index);

		if (l <= heapSize && heap[l].number <= heap[index].number)
		{
			largest = l;
			if (heap[l].number == heap[index].number && heap[l].indexArr > heap[index].indexArr)
				largest = index;
		}
		

		int larg = largest;

		if (r <= heapSize && heap[r].number <= heap[largest].number)
		{
			largest = r;
			if (heap[r].number == heap[larg].number && heap[r].indexArr > heap[larg].indexArr)
				largest = larg;
		}
		
		if (largest != index)
		{
			swap(heap[index].number, heap[largest].number);
			swap(maxHeap[heap[index].indexMax].indexMin, maxHeap[heap[largest].indexMax].indexMin);
			swap(heap[index].indexMax, heap[largest].indexMax);
			swap(heap[index].indexArr, heap[largest].indexArr);
			minHeapify(heap,maxHeap, largest, heapSize);
		}


	}

	void heapifyParentMin(Element *heap,Element* maxHeap, int index, int heapSize)
	{
		int par = parent(index);
		int largest = par;
		if (par >= 1 && heap[index].number <= heap[par].number)
		{
			largest = index;

			if (heap[index].number == heap[par].number && heap[index].indexArr > heap[par].indexArr)
				largest = par;
		}


		if (largest != par)
		{
			swap(heap[par].number, heap[largest].number);
			swap(heap[par].indexArr, heap[largest].indexArr);
			swap(maxHeap[heap[par].indexMax].indexMin, maxHeap[heap[largest].indexMax].indexMin);
			swap(heap[par].indexMax, heap[largest].indexMax);
			heapifyParentMin(heap, maxHeap, par, heapSize);
		}
	}

	void heapifyParentMax(Element *heap,Element * minHeap, int index, int heapSize)
	{
		
		int par = parent(index);
		int largest = par;
		if (par >= 1 && heap[index].number >= heap[par].number)
		{
			largest = index;

			if (heap[index].number == heap[par].number && heap[index].indexArr > heap[par].indexArr)
				largest = par;
		}
		

		if (largest != par)
		{
			swap(heap[par].number, heap[largest].number);
			swap(heap[par].indexArr, heap[largest].indexArr);
			swap(minHeap[heap[par].indexMin].indexMax, minHeap[heap[largest].indexMin].indexMax);
			swap(heap[par].indexMin, heap[largest].indexMin);
			heapifyParentMax(heap,minHeap, par, heapSize);
		}
	}
	void deleteMin(Element* heap,Element *maxHeap, int& heapSize, int index)
	{
		if (index != heapSize)
		{
			heap[index].number = heap[heapSize].number;
			heap[index].indexArr = heap[heapSize].indexArr;
			heap[index].indexMax = heap[heapSize].indexMax;
			maxHeap[heap[heapSize].indexMax].indexMin = index;
		}
		heapSize--;
		minHeapify(heap, maxHeap, index, heapSize);
		heapifyParentMin(heap, maxHeap, index, heapSize);
	}

	void buildMinHeap(Element *heap, Element* maxHeap, int heapSize)
	{
		for (int i = parent(heapSize); i > 0; i--)
			minHeapify(heap,maxHeap, i, heapSize);
	}



	void maxHeapify(Element *heap,Element* minHeap, int index, int heapSize)
	{
		int largest = index;
		Element tmp;
		int l = left(index);
		int r = right(index);

		if (l <= heapSize && heap[l].number >= heap[index].number)
		{
			largest = l;
			if (heap[l].number == heap[index].number && heap[l].indexArr > heap[index].indexArr)
				largest = index;
		}


		int larg = largest;

		if (r <= heapSize && heap[r].number >= heap[largest].number)
		{
			largest = r;
			if (heap[r].number == heap[larg].number && heap[r].indexArr > heap[larg].indexArr)
				largest = larg;
		}

		if (largest != index)
		{
			swap(heap[largest].number, heap[index].number);
			swap(minHeap[heap[index].indexMin].indexMax, minHeap[heap[largest].indexMin].indexMax);
			swap(heap[largest].indexMin, heap[index].indexMin);
			swap(heap[largest].indexArr, heap[index].indexArr);
			maxHeapify(heap,minHeap, largest, heapSize);
		}

	}



	void deleteMax(Element* heap,Element* minHeap, int& heapSize, int index)
	{
		if (index != heapSize)
		{
			heap[index].number = heap[heapSize].number;
			heap[index].indexArr = heap[heapSize].indexArr;
			heap[index].indexMin = heap[heapSize].indexMin;
			minHeap[heap[heapSize].indexMin].indexMax = index;
		}
		heapSize--;
		maxHeapify(heap, minHeap, index, heapSize);
		heapifyParentMax(heap, minHeap, index, heapSize);
	}

	void buildMaxHeap(Element *heap,Element* minHeap, int heapSize)
	{
		for (int i = parent(heapSize); i > 0; i--)
			maxHeapify(heap,minHeap, i, heapSize);
	}


int main()
{
	int n;
	__int64 num;
	char c =' ';
	int numberOfCollatz;
	int q;
	int MinSize = 0;
	int MaxSize = 0;
	scanf("%d", &n);
	int heapSize = n;
	Element* minHeap = new Element[n + 1];
	Element* maxHeap = new Element[n + 1];
	Element* arr = new Element[n + 1];
	int iH = 1; //indeksy min i max


	for (int i = 1; i < n + 1; i++)
	{
		scanf("%u", &arr[i].number);
		if (arr[i].number != 1)
		{
			maxHeap[iH].number = arr[i].number;
			minHeap[iH].number = arr[i].number;
			maxHeap[iH].indexArr = i;
			maxHeap[iH].indexMax = iH;
			maxHeap[iH].indexMin = iH;
			minHeap[iH].indexArr = i;
			minHeap[iH].indexMax = iH;
			minHeap[iH].indexMin = iH;
			arr[i].check = ' ';
			iH++;
			MaxSize++;
			MinSize++;
		}
	}

	buildMaxHeap(maxHeap,minHeap, MaxSize);
	buildMinHeap(minHeap,maxHeap, MinSize);
	
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		scanf("%d %c", &numberOfCollatz, &c);

		if (c == 's')
		{
			for (int j = 0; j < numberOfCollatz; j++)
			{
				if (MinSize > 0 && MaxSize > 0)
				{
					num = minHeap[1].number;

					if (num % 2 == 0)
					{
						num = num / 2;

					}
					else
						num = 3 * num + 1;

					if (num > 4294967295)
					{
						arr[minHeap[1].indexArr].check = 'm';

						deleteMax(maxHeap, minHeap, MaxSize, minHeap[1].indexMax);
						deleteMin(minHeap, maxHeap, MinSize, 1);
					}
					else
					{
						if (minHeap[1].number % 2 == 0)
						{
							minHeap[1].number = minHeap[1].number / 2;
							maxHeap[minHeap[1].indexMax].number = minHeap[1].number;
							if (minHeap[1].number == 1)
							{
								arr[minHeap[1].indexArr].number = 1;
								deleteMax(maxHeap, minHeap, MaxSize, minHeap[1].indexMax);
								deleteMin(minHeap, maxHeap, MinSize, 1);
							}
							else
							{
								arr[minHeap[1].indexArr].number = minHeap[1].number;
								maxHeapify(maxHeap, minHeap, minHeap[1].indexMax, MaxSize);
							}
						}
						else
						{
							minHeap[1].number = 3 * minHeap[1].number + 1;
							maxHeap[minHeap[1].indexMax].number = minHeap[1].number;
							arr[minHeap[1].indexArr].number = minHeap[1].number;
							heapifyParentMax(maxHeap, minHeap, minHeap[1].indexMax, MaxSize);
							minHeapify(minHeap, maxHeap, 1, MinSize);
						}


					}
				}
			}
		}

		if (c == 'l' )
		{
			for (int k = 0; k < numberOfCollatz; k++)
			{
				if (MinSize > 0 && MaxSize > 0)
				{
					num = maxHeap[1].number;

					if (num % 2 == 0)
					{
						num = num / 2;

					}
					else
						num = 3 * num + 1;

					if (num > 4294967295)
					{
						arr[maxHeap[1].indexArr].check = 'm';
						deleteMin(minHeap, maxHeap, MinSize, maxHeap[1].indexMin);
						deleteMax(maxHeap, minHeap, MaxSize, 1);
					}
					else
					{
						if (maxHeap[1].number % 2 == 0)
						{
							maxHeap[1].number = maxHeap[1].number / 2;
							minHeap[maxHeap[1].indexMin].number = maxHeap[1].number;
							arr[maxHeap[1].indexArr].number = maxHeap[1].number;
							if (maxHeap[1].number == 1)
							{
								deleteMin(minHeap, maxHeap, MinSize, maxHeap[1].indexMin);
								deleteMax(maxHeap, minHeap, MaxSize, 1);

							}
							else
							{
								heapifyParentMin(minHeap, maxHeap, maxHeap[1].indexMin, MinSize);
								maxHeapify(maxHeap, minHeap, 1, MaxSize);
							}
						}
						else
						{
							maxHeap[1].number = 3 * maxHeap[1].number + 1;
							minHeap[maxHeap[1].indexMin].number = maxHeap[1].number;
							arr[maxHeap[1].indexArr].number = maxHeap[1].number;
							minHeapify(minHeap, maxHeap, maxHeap[1].indexMin, MinSize);
						}


					}


				}
			}
		}
	}

	for (int i = 1; i < heapSize + 1; i++)
	{
		if (arr[i].check == 'm')
		{
			putchar('m');
			putchar(' ');
		}
		else
		printf("%u ", arr[i].number);
	}
	
	/*printf("\n");
	for (int i = 1; i<heapSize + 1; i++)
		printf("%u ", minHeap[i].number);
	printf("\n");
	for (int i = 1; i<heapSize + 1; i++)
		printf("%u ", maxHeap[i].number);
	printf("\n");*/

    return 0;
}

