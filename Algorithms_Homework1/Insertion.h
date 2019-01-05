#pragma once
#include "SortAlgorithm.h"

class Insertion:public SortAlgorithm
{
public:
	Insertion(void);
	~Insertion(void);
	void Sort(int* Array,const int & size); //main function for sorting
};



Insertion::Insertion(void)
{
}

void Insertion::Sort(int* array,const int & size)
{
	if(array==NULL ||size<1)
		return;
	for(int i=1;i<size;i++)
	{
		int value=array[i],j=i-1;
		while(j>=0 && array[j]>value)
			array[j+1]=array[j],j--;
		array[j+1]=value;
	}
}

Insertion::~Insertion(void)
{
}


