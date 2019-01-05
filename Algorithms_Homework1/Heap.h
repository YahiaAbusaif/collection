#pragma once
#include "SortAlgorithm.h"


class Heap :public SortAlgorithm
{
	
	void BuildMaxHeab(); // function for build initial Heab
	void MaxHeab(const int & index); // check for element[index] if it is bigger than its child else fix it
public:
	Heap(void);
	~Heap(void);
	void Sort(int* array,const int & size); //main function for sorting
	
	int parent(const int & index); //return parent of index
	int left(const int & index); //return left childern of index
	int right(const int & index); //return right childern of index
};



Heap::Heap(void)
{
}

void Heap::Sort(int* array,const int & size)
{
	if(array==NULL ||size<1)
		return;
	MainArray=array;
	Size=size;
	//build the heab 
	BuildMaxHeab();
	while(Size>1)
	{
		Size--;
		//exchange the maximum number (MainArray[0]) and put it in his correct position (index)
		this->swap(0,size);
		//fix heab 
		MaxHeab(0);
	}
}



void Heap::BuildMaxHeab()
{
	int index=Size>>1; //end of heab floor(size/2)
	while (index>=0)
	{
		MaxHeab(index);
		index--;
	}
}

void Heap::MaxHeab(const int & index)
{
	int R=right(index),L=left(index),Largest=index;
	//check if childern are bigger than the parent
	if(L<Size && MainArray[L]>MainArray[Largest])
		Largest=L;
	if(R<Size && MainArray[R]>MainArray[Largest])
		Largest=R;
	//if yes exchange it and check again 
	if(Largest!=index)
	{
		this->swap(index,Largest);
		MaxHeab(Largest);
	}

}

int Heap::parent(const int & index)
{
	return index>>1; //index / 2
}
int Heap::left(const int & index)
{
	return (index<<1)+1;//index*2+1
}
int Heap::right(const int & index)
{
	return (index+1)<<1;//index*2+2 or(index+1)*2
}

Heap::~Heap(void)
{
}

