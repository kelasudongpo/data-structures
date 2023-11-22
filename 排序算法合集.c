#include<stdio.h>
typedef int ElementType;
ElementType A[100];
void insert_sort (ElementType A[], int N);
void Shell_sort (ElementType A[], int N);
void Heap_sort (ElementType A[], int N);
void Merge_sort (ElementType A[], int N);
void MSort (ElementType A[], ElementType TmpArray[], int Left, int Right);
void Merge (ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd);
void Quick_sort (ElementType A[], int Left, int Right);
ElementType Median3(ElementType A[], int Left, int Right);
void Select_sort (ElementType A[], int N);
void Boom_sort (ElementType A[], int N);
/*测试用例
10
3 5 6 8 7 9 1 2 4 10*/
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0 ; i < n ; i++)
		scanf("%d" ,&A[i]);
	Boom_sort (A,n);
	for (int i = 0 ; i < n ; i++)
		printf("%d\n" ,A[i]);
} 
void insert_sort (ElementType A[], int N) //插入排序
{
	int i,j;
	ElementType Temp;
	for (i = 1 ; i < N ; i++)
	{
		Temp = A[i];
		for (j = i ;j > 0 && A[j-1] > Temp ; j--)
			A[j] = A[j-1];
		A[j] = Temp;
	}
}
void Shell_sort (ElementType A[], int N)  //希尔排序，增量序列每次为总长度折半
{
	int i, j, Increment;
	ElementType Temp;
	for (Increment = N/2 ; Increment > 0 ; Increment /= 2)
	{
		for (i = Increment ; i < N ; i++)
		{
			Temp = A[i];
			for (j = i ; j >= Increment ; j -= Increment)
			{
				if (Temp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			}
			A[j] = Temp;
		}
	}
}
void PercDown (ElementType A[], int i, int N)
{
	int child;
	ElementType Temp;
	for (Temp = A[i] ; 2*i + 1 < N ; i = child)
	{
		child = 2*i + 1;
		if (child != N-1 && A[child + 1] > A[child])
			child++;
		if (Temp < A[child])
			A[i] = A[child];
		else
			break;
	}
	A[i] = Temp;
}
void Swap (ElementType *a, ElementType *b)
{
	ElementType Temp;
	Temp = *a;
	*a = *b;
	*b = Temp;
}
void Heap_sort (ElementType A[], int N)  //堆排序
{
	int i;
	for (i = N/2 ; i >= 0 ; i--)  //建堆
		PercDown (A, i, N);
	for (i = N - 1 ; i > 0 ; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}		
}
void MSort (ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right)/2;
		MSort (A, TmpArray, Left, Center);
		MSort (A, TmpArray, Center + 1, Right);
		Merge (A, TmpArray, Left, Center + 1, Right);
	}
}
void Merge_sort (ElementType A[], int N)
{
	ElementType *TmpArray;

	TmpArray = malloc (N * sizeof(ElementType));
	if (TmpArray != NULL)
	{
		MSort (A, TmpArray, 0, N-1);
		free (TmpArray);
	}
	else 
		printf("No space for tmp array!!");
}
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;
	while (Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else	
			TmpArray[TmpPos++] = A[Rpos++];
	}
	while (Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];
	for (i = 0 ; i < NumElements ; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right)/2;
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];
}
Quick_sort (ElementType A[], int Left, int Right)
{
	int i, j, cutoff = 3;
	ElementType pivot;
	if (Left + cutoff <= Right)
	{
		pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;
		while(1)
		{
			while (A[++i] < pivot);
			while (A[--j] > pivot);
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap (&A[i], &A[Right - 1]);
		Quick_sort(A, Left, i-1);
		Quick_sort(A, i+1, Right);
	}
	else
		insert_sort(A+Left, Right - Left +1);
}
Select_sort (ElementType A[], int N)
{
	int i, j;
	for (i = 0 ; i < N ; i++)
	{
		int min = i;
		for (j = i + 1 ; j < N ; j++)
		{
			if (A[j] < A[min])
				min = j;
		}
		Swap(&A[i], &A[min]);
	}
}
Boom_sort (ElementType A[], int N)
{
	int i, j;
	for (i = 0 ; i < N-1 ; i++)
	{
		for (j = 0 ; j <= N-i-2 ; j++)
		{
			if (A[j] > A[j+1])
				Swap(&A[j], &A[j+1]);
		}
	}
}
