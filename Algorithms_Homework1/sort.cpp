#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <memory.h>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <valarray>
#include <fstream>
#include <chrono>
#include <vector>

#include "SortAlgorithm.h"
#include "Selection.h"
#include "Insertion.h"
#include "Merge.h"
#include "Quick.h"
#include "Heap.h"
#include "Hybrid.h"

using namespace std;



bool issorted=0;// check if data is sorted

long long sort(int *array,const int & select,const int & size)
{
	//decide which algorithm we are going to use dependens on select
	SortAlgorithm *CurrentAlgorithm=NULL;
	switch (select)
	{
		case 0:
			CurrentAlgorithm= new Selection; 
			break;
		case 1: 
			CurrentAlgorithm= new Insertion;
			break;
		case 2: 
			CurrentAlgorithm= new Merge;
			break;
		case 3: 
			CurrentAlgorithm= new Quick;
			break;
		case 4: 
			CurrentAlgorithm= new Heap;
			break;
		case 5: 
			CurrentAlgorithm= new Hybrid;
			break;
		default:	
			break;
	}
	//if Null that means user enterd invalid select
	if(CurrentAlgorithm==NULL)
		return -1;
	issorted=CurrentAlgorithm->check(array,size); //this for testing for unsorted and sorted data
	//else sort the array using the algo
	auto started = chrono::high_resolution_clock::now();
	CurrentAlgorithm->Sort(array,size);
	auto done = chrono::high_resolution_clock::now();
	//check if array sorted 
	if(!(CurrentAlgorithm->check(array,size)))
		return -1;
	return chrono::duration_cast< chrono::milliseconds >(done-started).count();
}




int main(int argc, char* argv[])
{
	//check if there are any missing data
	if(argc<5)
		return 1;

	//take input from user 
	int select=atoi(argv[1]);

	ifstream inputfile;
	vector <int> refernce;
	inputfile.open(argv[2],ios::in); 
   	if(!inputfile) 
		return 1;
   	int currentnumber;
	while(!(inputfile.eof()))
	{
		currentnumber=2147483640;//infinte number for int 32 bit 
		inputfile>>currentnumber;
		if(currentnumber!=2147483640)
			refernce.push_back(currentnumber);
	}
       
	
	//convert input to deynmic data for processing 
	int size=refernce.size();
	int *array=new int[size];
	for(int i=0;i<size;i++)
		array[i]=refernce[i];
	
	//sort data
	int result=sort(array,select,size);

	//check if there are any error while sorting
	if(result<0)
		return 1;
	//print the sorted list to file
	FILE * sortedout= fopen (argv[3],"w");
	if(sortedout==NULL)
		return 1;
	for(int i=0;i<size;i++)
	{
		string current =to_string(array[i])+"\n";
		char const *output = current.c_str(); 
		fputs (output,sortedout);
	}
	fclose (sortedout);
	
	//print time spent to the another file
	FILE * timespent= fopen (argv[4],"a");
	if(timespent==NULL)
		return 1;
	string state;
	if(issorted)
		state="_sorted: ";
	else
		state="_unsorted: ";
	string outputtime =to_string(size)+state+to_string(result)+"ms taken\n";
	char const *pchar = outputtime.c_str(); 
	fputs (pchar,sortedout);
	fclose (sortedout);
	return 0;
}


