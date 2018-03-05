#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vld.h>

#define ARRAY_LENTH 100000

typedef struct QUICK
{
	int leftlen;
	int rightlen;
	int low;
	int high;
}QUICK;


bool IsOrderly(int *arr, int len)//��������Ƿ�����
{
	for (int i = 0; i < len - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
	return true;
}

//Խ����Խ��
void InsertSort(int *arr, int len)//����
{
	int i;
	int j;
	int tmp;
	for (i = 1; i < len; i++)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] > tmp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = tmp;
	}
}




static void Shell(int *arr, int len, int gpa)
{
	int i;
	int j;
	int tmp;
	for (i = gpa; i < len; i++)
	{
		tmp = arr[i];
		for (j = i - gpa; j >= 0; j -= gpa)
		{
			if (arr[j] > tmp)
			{
				arr[j + gpa] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + gpa] = tmp;
	}
}

void ShellSort(int *arr, int len)//ϣ��
{
	int gpa[] = {7,5,3,1};

	for (int i = 0; i < sizeof(gpa) / sizeof(gpa[0]); i++)
	{
		Shell(arr, len, gpa[i]);
	}
}

static void Swap(int *arr, int low, int high) 
{
	int tmp = arr[low];
	arr[low] = arr[high];
	arr[high] = tmp;
}

static int Pivotkey(int *arr, int low, int high)//����ȡ��
{
	int mid = (high - low) / 2 + low;

	if (arr[low] > arr[high])
	{
		Swap(arr, low, high);
	}
	if (arr[mid] > arr[high])
	{
		Swap(arr, mid, high);
	}
	//��������������high����low��mid
	if (arr[mid] > arr[low])
	{
		Swap(arr, mid, low);
	}
	//��������������mid <= low <= high
	return arr[low];
}

static int Partition(int *arr, int low, int high, int *pleftlen, int *prightlen)//����ȡ�мӴ�����ȵ�����
{
	int pivot = Pivotkey(arr, low, high);

	//����Ϊ0
	*pleftlen = 0;
	*prightlen = 0;

	//����������������׼��ʱʹ��
	int first = low;
	int last = high;

	//��������������ʱʹ��
	int left = low;
	int right = high;
	

	while (low < high)
	{
		while ((low < high) && arr[high] >= pivot)
		{
			if (arr[high] == pivot)
			{
				Swap(arr, high, right);
				right--;
				(*prightlen)++;
			}
			high--;
		}
		arr[low] = arr[high];
		while ((low < high) && arr[low] <= pivot)
		{
			if (arr[low] == pivot)
			{
				Swap(arr, low, left);
				left++;
				(*pleftlen)++;
			}
			low++;
		}
		arr[high] = arr[low];
	}
	arr[low] = pivot;

	//��������ȵ��Ƶ�low������
	int i = first;
	int j = low - 1;
	while (i < left && arr[j] != pivot)
	{
		Swap(arr, i, j);
		i++;
		j--;
	}

	i = low + 1;
	j = last;
	while (j > right && arr[i] != pivot)
	{
		Swap(arr, i, j);
		i++;
		j--;
	}

	return low;
}

static void Quick(int *arr, int low, int high)
{
	if (low < high)
	{
		int leftlen;
		int rightlen;

		int par = Partition(arr, low, high, &leftlen, &rightlen);

		Quick(arr, low, par - 1 - leftlen);
		Quick(arr, par + 1 + rightlen, high);
	}
}

static void Quick1(int *arr, int head, int tail)//�ǵݹ��
{
	if (head >= tail)
	{
		return;
	}

	int leftlen;
	int rightlen;
	int low = head;
	int high = tail;

	int count = 0;//��ջ��Ԫ�صĸ���

	int par = Partition(arr, low, high, &leftlen, &rightlen);
	QUICK *quick = (QUICK *)malloc(++count * sizeof(QUICK));
	quick[count - 1].low = low;
	quick[count - 1].high = high;
	quick[count - 1].leftlen = leftlen;
	quick[count - 1].rightlen = rightlen;

	low = quick[count - 1].low;
	high = par - 1 - leftlen;

	while (count >= 0)
	{
		while (low < high)
		{
			par = Partition(arr, low, high, &leftlen, &rightlen);

			quick = (QUICK *)realloc(quick, ++count * sizeof(QUICK));

			quick[count - 1].low = low;
			quick[count - 1].high = high;

			quick[count - 1].leftlen = leftlen;
			quick[count - 1].rightlen = rightlen;

			low = quick[count - 1].low;
			high = par - 1 - leftlen;
		}

		low = par + 1 + rightlen;
		high = quick[count - 1].high;
		count -= 1;
	}
	

	free(quick);
}

void QuickSort(int *arr, int len)//����
{
	Quick1(arr, 0, len - 1);
}




void BubbleSort(int *arr, int len)//ð��
{
	int i;
	int j;
	int tmp;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}


void SelectSort(int *arr, int len)//ѡ��
{
	int i;
	int j;
	int min_index;
	int tmp;
	for (i = 0; i < len - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		tmp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = tmp;
	}
}

static void HeapAdjust(int *arr, int start, int end)
{
	int parent = start;

	for (int i = start * 2 + 1; i <= end; i = i * 2 + 1)
	{
		if ((i + 1) <= end && arr[i] < arr[i + 1])//��iָ������������ֵ����Ǹ�
		{
			i += 1;
		}

		if (arr[i] > arr[parent])//�������С�ں��ӣ��ǾͰѺ��Ӹ����׵�����Ȼ����¸���
		{
			int tmp = arr[parent];
			arr[parent] = arr[i];
			arr[i] = tmp;

			parent = i;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *arr, int len)//����
{
	for (int i = (len - 1) / 2 ; i >= 0; i--)
	{
		HeapAdjust(arr, i, len - 1);
	}

	for (int i = 0; i < len; i++)
	{
		int tmp = arr[0];
		arr[0] = arr[len - 1 - i];
		arr[len - 1 - i] = tmp;

		HeapAdjust(arr, 0, len - 1 - i - 1);
	}
}

static void Merge(int *arr, int len, int gap)
{
	//�����������鲢��
	int low1 = 0;
	int high1 = low1 + gap - 1;//high1�����ж��ǲ���Խ���ˣ���Ϊֻ��ȥ�����ıȽϣ������high1������
	int low2 = high1 + 1;
	int high2 = low2 + gap - 1 < len ? low2 + gap - 1 : len - 1;//high2��Ҫ�ж��Ƿ�Խ���ˣ���Ϊ����Ҫ��high2�����õ�

	int *brr = (int *)malloc(len * sizeof(int));
	int i = 0;

	while (low2 < len)//���������鲢��
	{
		while (low1 <= high1 && low2 <= high2)
		{
			if (arr[low1] <= arr[low2])
			{
				brr[i++] = arr[low1++];
			}
			else
			{
				brr[i++] = arr[low2++];
			}
		}

		while (low1 <= high1)
		{
			brr[i++] = arr[low1++];
		}
		while (low2 <= high2)
		{
			brr[i++] = arr[low2++];
		}

		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap - 1 < len ? low2 + gap - 1 : len - 1;
	}

	while (low1 < len)//ֻ��һ���鲢��//��Ϊǰ����low2 < lenʧ���ˣ�Ҳ����û�������鲢�����ԣ����ֻҪlow1 < len�����ǻ���һ���鲢��
	{
		brr[i++] = arr[low1++];
	}

	for (int i = 0; i < len; i++)//��arr�����ݻ�����
	{
		arr[i] = brr[i];
	}
	free(brr);
}

void MergeSort(int *arr, int len)//�鲢
{
	for (int gap = 1; gap < len; gap *= 2)
	{
		Merge(arr, len, gap);
	}
}

int maain()
{
	int arr[] = {3,6,1,3,7,8,5,12,2,9};

	QuickSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}

int main()
{
	clock_t start, end;

	int *arr = (int *)malloc(ARRAY_LENTH * sizeof(int));
	for (int i = 0; i < ARRAY_LENTH; i++)
	{
		//arr[i] = 10;
		arr[i] = rand() * rand();
	}

	start = clock();
	//InsertSort(arr, ARRAY_LENTH);//Լ����7.5��
	//ShellSort(arr, ARRAY_LENTH);//Լ����1.2��
	//QuickSort(arr, ARRAY_LENTH);//Լ����23����
	//BubbleSort(arr, ARRAY_LENTH);//Լ����33��
	//SelectSort(arr, ARRAY_LENTH);//Լ����13.9��
	//HeapSort(arr, ARRAY_LENTH);//Լ����30����
	MergeSort(arr, ARRAY_LENTH);//Լ����21����
	end = clock();

	if (IsOrderly(arr, ARRAY_LENTH))
	{
		printf("����\n");
	}
	else
	{
		printf("����\n");
	}

	printf("%d\n", end - start);

	free(arr);

	return 0;
}