#pragma once
#include "SortAlgorithm.h"

class Quick:public SortAlgorithm
{
	int partition(int Start,int End); //to process the partitions
	void divide(int Start,int End); //to divide the range
public:
	Quick(void);
	~Quick(void);
	
	void Sort(int* Array,const int & size); //main function for sorting
};



Quick::Quick(void)
{
}

void Quick::Sort(int* array,const int & size)
{
	//intilize
	if(array==NULL ||size<1)
		return;
	MainArray=array;
	Size=size;
	divide(0,size-1);
}

void Quick::divide(int Start,int End)
{
	if(Start<End)
	{
		int middle=partition(Start,End);
		divide(Start,middle-1);
		divide(middle+1,End);
	}
}



int Quick::partition(int first, int last)
{
	int pivot=(last+first)>>1,index, smallIndex;
	this->swap(first, pivot);
	pivot = MainArray[first];
	smallIndex = first;
	for (index = first + 1; index <= last; index++)
	{
		if (MainArray[index] < pivot)
		{
			smallIndex++;
			this->swap(smallIndex, index);
		}
	}
	this->swap(first,smallIndex);
	return smallIndex;
}

/*
int Quick::partition(int Start,int End)
{
	int value=MainArray[End]; //the value that we divide the array according to it
	int index=Start-1; //set value for the posititon that can switch 
	for(int Iterator=Start;Iterator<End;Iterator++)
	{
		if(MainArray[Iterator]<=value)
		{
			index++;
			//switch the 2 elements
			int current=MainArray[index];
			MainArray[index]=MainArray[Iterator];
			MainArray[Iterator]=current;
		}
	}
	//put the value in the corrct position and return the position
	index++;
	int current=MainArray[index];
	MainArray[index]=MainArray[End];
	MainArray[End]=current;
	return index;
}*/



Quick::~Quick(void)
{
}


