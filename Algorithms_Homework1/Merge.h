#pragma once
#include "SortAlgorithm.h"

class Merge:public SortAlgorithm
{
	int* RightArray; // array for copy right array
	int* LeftArray; // array for copy Left array
	void divide(int Right,int Left); //divide the range to 2 part and sort them then marge
	void sortpart(int Right,int middel,int Left); // marge 2 parts & sorted them
public:
	Merge(void);
	~Merge(void);
	void Sort(int* Array,const int & size); //main function for sorting
};





Merge::Merge(void)
{
}


void Merge::Sort(int* array,const int & size)
{
	if(array==NULL ||size<1)
		return;
	MainArray=array;
	Size=size;
	RightArray=new int[size];
	LeftArray=new int[size];
	divide(0,size-1);
}

void Merge::divide(int Right,int Left)
{
	if(Right < Left)
	{
		int middel= (Right+Left)>>1; //get middle pointer
		divide(Right,middel); //solve Right part
		divide(middel+1,Left); //solve Left part
		sortpart(Right,middel,Left); //merge the 2 part
	}
}

void Merge::sortpart(int Right,int middel,int Left)
{
	int index;

	index=0; //make copy of from Right to middle at first Array
	for(int i=Right;i<=middel;i++)
	{
		RightArray[index]=MainArray[i];
		index++;
	}
	RightArray[index]=2147483647; // add (maximum value for int 16 bit) to the end of array
	
	index=0; //make copy of from middle+1 to Left at second Array
	for(int i=middel+1;i<=Left;i++)
	{
		LeftArray[index]=MainArray[i];
		index++;
	}
	LeftArray[index]=2147483647; // add (maximum value for int 16 bit) to the end of array

	int index1=0,index2=0; //pointer for the 2 array
	for(int i=Right;i<=Left;i++)
	{
		if(RightArray[index1]<LeftArray[index2])
		{
			MainArray[i]=RightArray[index1];
			index1++;
		}
		else
		{
			MainArray[i]=LeftArray[index2];
			index2++;
		}
	}
}

Merge::~Merge(void)
{
}
