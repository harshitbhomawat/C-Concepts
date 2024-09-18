#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Heap
{
	int currentSize, maxsize;
	vector<T> heap;
	void heapifyUp(int index)
	{
		if(index == 0)
		{
			return;
		}
		int parentIndex = (index%2==0?index/2 - 1:index/2);
		if(heap[parentIndex] < heap[index])
		{
			swap(heap[parentIndex],heap[index]);
			heapifyUp(parentIndex);
		}
		return;
	}
	void heapifyDown(int index)
	{
		int swapindex=-1;
		if(2*index + 2 < currentSize)
		{
			if(heap[2*index+1]>heap[2*index+2])
			{
				swapindex = 2*index+1;
			}
			else
			{
				swapindex = 2*index+2;
			}
		}
		else if(2*index+1<currentSize)
		{
			swapindex = 2*index+1;
		}
		if(swapindex == -1)
		{
			return;
		}
		swap(heap[index],heap[swapindex]);
		heapifyDown(swapindex);
		return;
	}
	public:
	Heap(int maxsize)
	{
		currentSize=0;
		heap.resize(maxsize);
	}
	int size()
	{
		return currentSize;
	}
	void push(T val_)
	{
		if(currentSize == maxsize)
		{
			cout<<"Heap Full!"<<endl;
			return;
		}
		heap[currentSize] = val_;
		heapifyUp(currentSize);
		currentSize++;
	}
	T top()
	{
		return heap[0];
	}
	void pop()
	{
		if(currentSize == 0)
		{
			cout<<"Heap Empty!"<<endl;
			return;
		}
		currentSize--;
		int parentIndex = (currentSize%2==0?currentSize/2 - 1:currentSize/2);
		swap(heap[currentSize],heap[parentIndex]);
		heapifyDown(0);
	}
};
int main()
{
	Heap<double> heap(9);
	heap.push(2);
	heap.push(3);
	heap.push(10.5);
	heap.push(7);
	heap.push(5.3);
	heap.push(15.2);
	heap.push(4);
	heap.push(9);
	heap.pop();
	cout<<heap.top()<<endl;
}
