#include <bits/stdc++.h> 
using namespace std;

int Infinte=2147483640;

int *Array;
int *SortedArray;

//function to compare 2 pair of integer 
bool compare(const pair<int,int> &first,const pair<int,int> & second) 
{
	if(first.first==second.first)
		return first.second<second.second;
	return (first.first>second.first);
}

long long frequencySort(const int & Size)
{
	if(Array==NULL || Size<1) //validation
		return -1;
	SortedArray=new int[Size];
	auto started = chrono::high_resolution_clock::now(); //start time
	unordered_map<int,int> frequencyCounter; //for frequancy
	//calculte frequency
	for(int index=0;index<Size;index++)
		frequencyCounter[Array[index]]++;
	//push the result
	int SizeUnique=frequencyCounter.size();
	pair<int,int> * result=new pair<int,int>[SizeUnique]; //for storing the result
	int index=0;
	for(unordered_map<int,int>::iterator it=frequencyCounter.begin();it!=frequencyCounter.end();it++)
		result[index++]=make_pair((*it).second,(*it).first);
	
	//sort the array 
	sort(result,result+SizeUnique,compare);	
	//push all elements to the new array 
	int Last=0;
	for(int index=0;index<SizeUnique;index++)
	{
		for(int iter=0;iter<result[index].first;iter++)
			SortedArray[Last++]=result[index].second;
	}
	auto done = chrono::high_resolution_clock::now(); //end time
	return chrono::duration_cast< chrono::milliseconds >(done-started).count(); //return the time 
}



int main(int argc, char* argv[])
{
	if(argc<3) //if number of argument less than requird end the program 
		return 1;

	//open input file
	fstream inputfile;
  	inputfile.open(argv[1],ios::in); 
    	if(!inputfile) //if can not open file end the program 
		return 1;
	//Read data from the file
	vector <int> refernce;
	while(!(inputfile.eof()))
	{
		int currentnumber=Infinte;
		inputfile>>currentnumber;
		if(currentnumber!=Infinte)
			refernce.push_back(currentnumber);
	}
	//convert it to static array 
	int size=refernce.size();
	Array=new int[size];
	for(int i=0;i<size;i++)
		Array[i]=refernce[i];

	//process
	long long TotalTime=frequencySort(size);

	//print the result
	FILE * sortedout= fopen (argv[2],"w");
	if(sortedout==NULL)//if can not open file end the program 
		return 1;
	for(int index=0;index<size;index++)
	{
		string current =to_string(SortedArray[index])+"\n";
		char const *output = current.c_str(); 
		fputs (output,sortedout);
	}
	fclose (sortedout);
	
	//print the time
	FILE * TimeSpent= fopen (argv[3],"w");
	if(TimeSpent==NULL) //if can not open file end the program 
		return 1;
	string outputtime =to_string(TotalTime)+"\n";
	char const *pchar = outputtime.c_str(); 
	fputs (pchar,TimeSpent);
	fclose (TimeSpent);

	return 0;
}

