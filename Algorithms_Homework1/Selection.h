#pragma once
#include "SortAlgorithm.h"

class Selection:public SortAlgorithm
{
public:
	Selection(void);
	~Selection(void);
	void Sort(int* Array,const int & size); //main function for sorting
};


Selection::Selection(void)
{
}


void Selection::Sort(int* array,const int & size)
{
	if(array==NULL ||size<1)
		return;
	MainArray=array;
	Size=size;
	for(int index=0;index<size;index++)
	{
		int minimum=index;
		for(int Iterator=index+1;Iterator<size;Iterator++)
		{
			if(array[Iterator]<array[minimum])
				minimum=Iterator;
		}
		this->swap(index,minimum);
	}
}


Selection::~Selection(void)
{
}


