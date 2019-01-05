#include <bits/stdc++.h> 
using namespace std;

int Infinte=2147483640;
int *Array;
int *Result;

int Minimum(const int & Size,const int & K)
{
	if(Array==NULL || Size<1||K>Size) //validation 
		return -1;
	auto started = chrono::high_resolution_clock::now(); //start time 
	Result=new int[Size]; //set result by infinte number
	for(int iter=0;iter<Size;iter++)
		Result[iter]=Infinte;
	int Counter=0; //last element with minimum value
	for(int iter=0;iter<Size;iter++)
	{
		int index=iter,End=min(iter+K,Size);
		for(;index<End;index++)
		{
			if(Array[iter]>Array[Counter]||Counter==Size)
				break;
			Result[Counter]=min(Array[iter],Result[Counter]);	
			Counter++;
		}
		if(index==End) //if out of scope counter step back 
			Counter=iter+1;
		if(Counter==Size)
			break;
	}
	auto done = chrono::high_resolution_clock::now(); //end time 
	return chrono::duration_cast< chrono::milliseconds >(done-started).count(); //return algorithm time
}



int main(int argc, char* argv[])
{
	if(argc<4) //if not enough argument end the program 
		return 1;

	int K=atoi(argv[1]);
	//Read data from the file
	fstream inputfile;
    	inputfile.open(argv[2],ios::in); 
    	if(!inputfile) //if can't open file End the program 
		return 1;
	vector <int> refernce;
	while(!(inputfile.eof()))
	{
		int currentnumber=Infinte;
		inputfile>>currentnumber;
		if(currentnumber!=Infinte)
			refernce.push_back(currentnumber);
	}
	//convert input to deynmic data for processing 
	int Size=refernce.size();
	Array=new int[Size];

	for(int i=0;i<Size;i++)
		Array[i]=refernce[i];
	
	//sort data
	int TotalTime=Minimum(Size,K);
	//print 
	FILE * sortedout= fopen (argv[3],"w");
	if(sortedout==NULL)//if can't open file End the program 
		return 1;

	for(int index=K-1;index<Size;index++)
	{
		string current =to_string(Result[index])+"\n";
		char const *output = current.c_str(); 
		fputs (output,sortedout);
	}
	fclose (sortedout);

	FILE * TimeSpent= fopen (argv[4],"w");
	if(TimeSpent==NULL)//if can't open file End the program 
		return 1;
	string OutputTime =to_string(TotalTime)+"\n";
	char const *pchar = OutputTime.c_str(); 
	fputs (pchar,TimeSpent);
	fclose (TimeSpent);

	return 0;
}

