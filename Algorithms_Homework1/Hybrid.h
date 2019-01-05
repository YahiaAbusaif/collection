#pragma once
#include "SortAlgorithm.h"

class Hybrid :public SortAlgorithm
{
	int Point; //number of elemnts for quick or insertion 
	void divide(int Start,int End); //divide to 2 parts
	int partition(int Start,int End); //solve for pivot
	void insertionsort(int Left,int Right); //solve when range less than Point
public:
	Hybrid(void);
	~Hybrid(void);
	void Sort(int* array,const int & size); //main function for sorting
};



Hybrid::Hybrid(void)
{
}

void Hybrid::Sort(int* array,const int & size)
{
	//initlize
	if(array==NULL ||size<1)
		return;
	MainArray=array;
	Size=size;
	Point=100; //by try multi values
	divide(0,size-1);
	return;
}


void Hybrid::divide(int Start,int End)
{
	if(Start<End)
	{
		if(End-Start>Point)
		{
			int middle=partition(Start,End);
			divide(Start,middle-1);
			divide(middle+1,End);
		}
		else
			insertionsort(Start,End);

	}
}


int Hybrid::partition(int Start, int End)
{
	int pivot=(End+Start)>>1,smallIndex; //(end+start)/2
	this->swap(Start, pivot);//swap middle with first
	pivot = MainArray[Start];
	smallIndex = Start;
	for (int index = Start + 1; index <= End; index++)
	{
		if (MainArray[index] < pivot)//if index <pivot swap 
		{
			smallIndex++;
			this->swap(smallIndex, index);
		}
	}
	this->swap(Start, smallIndex);
	return smallIndex;
}

void Hybrid::insertionsort(int Left,int Right)
{

	for(int i=Left+1;i<=Right;i++)
	{
		int value=MainArray[i],j=i-1;
		while(j>=Left && MainArray[j]>value)
			MainArray[j+1]=MainArray[j],j--;
		MainArray[j+1]=value;
	}
}


Hybrid::~Hybrid(void)
{
}
