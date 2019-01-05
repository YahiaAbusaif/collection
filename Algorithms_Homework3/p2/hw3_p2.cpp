#include <bits/stdc++.h>
using namespace std;

#define lop(i,n) for(int i=0; i<n; i++)


vector<int> Array;
vector<int> Hight;

int solve(int index) //return the Hight of this node
{
	if(Hight[index]!=-1)
		return Hight[index];
	return Hight[index]=solve(Array[index])+1;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout<<"Error #argument";
		return 1;
	}

	ifstream InputFile;
	InputFile.open(argv[1]);
	if (!InputFile )
	{
		cout<<"Error can't open file";
		return 1;
	}
	//take the input
	int n;
	InputFile>>n;
	Array.resize(n);
	Hight.resize(n);
	lop(i,n)
	{
		InputFile>>Array[i];
		if(Array[i]==-1)
			Hight[i]=1;
		else
			Hight[i]=-1;
	}
	auto started = chrono::high_resolution_clock::now();	
	//solve the problem 
	int Answer=0;
	lop(i,n)
		Answer=max(Answer,solve(i));
	auto done = chrono::high_resolution_clock::now();
	long long timespent=chrono::duration_cast< chrono::milliseconds >(done-started).count();
	ofstream OutputFile,TimeFile;
	OutputFile.open(argv[2], ios::out);
	TimeFile.open(argv[3], ios::out);
	if (!OutputFile || !TimeFile )
	{
		cout<<"Error can't create file";
		return 1;
	}
	TimeFile << "Running time: " << timespent <<"ms\n";
	OutputFile << Answer << endl;
	return 0;
}

