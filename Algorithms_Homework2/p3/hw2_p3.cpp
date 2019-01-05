#include <bits/stdc++.h> 
using namespace std;

int Infinte=2147483640;

int *Array;

int MergeSort(const int & Size)
{
	if(Array==NULL || Size<1) //validation 
		return -1;
	auto started = chrono::high_resolution_clock::now();//start time

	int *AnotherArray=new int[Size];// array fot temp
	int DivideTo=1,index; //size of pieaces , index for iterator 
	while (DivideTo<Size)
	{
		index=0;
		while(index<Size)
		{
			int start1=index,start2=min(index+DivideTo,Size);
			index=min(start2+DivideTo,Size);

			//copy the 2 array
			for(int iter=start1;iter<start2;iter++)
				AnotherArray[iter]=Array[iter];
			for(int iter=start2;iter<index;iter++)
				AnotherArray[iter]=Array[iter];

			int p1=start1,p2=start2,iter;
			for(iter=start1;iter<index;iter++)
			{
				if(p1==start2||p2==index) //end of one array 
					break;
				else if( AnotherArray[p1]> AnotherArray[p2])
					Array[iter]=AnotherArray[p2++];
				else
					Array[iter]=AnotherArray[p1++];
			}
			//if only one end, copy the rest of the another at last of original array 
			while(p1<start2)
				Array[iter++]=AnotherArray[p1++];
			while(p2<index)
				Array[iter++]=AnotherArray[p2++];
		}
		DivideTo=(DivideTo<<1);//DivideTo*2 (double size of mergeing )
	}

	auto done = chrono::high_resolution_clock::now(); //end time 
	return chrono::duration_cast< chrono::milliseconds >(done-started).count(); //return algorithm time 
}



int main(int argc, char* argv[])
{
	if(argc<3) //check number of argument if not enough end the program 
		return 1;

	//Read data from the file
	fstream inputfile;
   	inputfile.open(argv[1],ios::in); 
    if(!inputfile) //if can not open the file end the program 
		return 1;
	vector <int> refernce;
	while(!(inputfile.eof()))
	{
		int currentnumber=Infinte;
		inputfile>>currentnumber;
		if(currentnumber!=Infinte)
			refernce.push_back(currentnumber);
	}

	//convert input to static data for processing 
	int size=refernce.size();
	Array=new int[size];
	for(int i=0;i<size;i++)
		Array[i]=refernce[i];
	
	//sort data
	int TotalTime=MergeSort(size);

	//print 
	FILE * sortedout= fopen (argv[2],"w");
	if(sortedout==NULL) //if can not open the file end the program 
		return 1;
	for(int index=0;index<refernce.size();index++)
	{
		string current =to_string(Array[index])+"\n";
		char const *output = current.c_str(); 
		fputs (output,sortedout);
	}
	fclose (sortedout);

	FILE * TimeSpent= fopen (argv[3],"w");
	if(TimeSpent==NULL) //if can not open the file end the program 
		return 1;
	string OutputTime =to_string(TotalTime)+"\n";
	char const *pchar = OutputTime.c_str(); 
	fputs (pchar,TimeSpent);
	fclose (TimeSpent);

	return 0;
}

