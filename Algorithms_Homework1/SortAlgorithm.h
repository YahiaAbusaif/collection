#pragma once
#include <iostream>
class SortAlgorithm
{
	protected:
	int* MainArray; //target array
	int Size; //size of array
public:
	SortAlgorithm(void);
	~SortAlgorithm(void);
	virtual void Sort(int* array,const int & size)//virtual function for sorting 
	{}
	bool check(int* arr, const int & size); //check if the functions sort all elements 
	void swap(const int & first,const int & second); //swap 2 elements
};



SortAlgorithm::SortAlgorithm(void)
{
}

void SortAlgorithm::swap(const int & first,const int & second)
{
	if(first>Size||second>Size||first<0||second<0)
		return;
	int current=MainArray[first];
	MainArray[first]=MainArray[second];
	MainArray[second]=current;
}

bool SortAlgorithm::check(int* arr, const int & size) 
{
	for(int i=0;i<size-1;i++)
		if(arr[i]>arr[i+1])
			return 0;
	return 1;
}

SortAlgorithm::~SortAlgorithm(void)
{
}

