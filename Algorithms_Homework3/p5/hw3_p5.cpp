#include <bits/stdc++.h>
using namespace std;

#define lop(i,n) for(int i=0; i<n; i++)
#define loop(i,start,n) for(int i=start; i<n; i++)

int n;
string s;

int CalcLen(pair<int,int> const & tar) //calculate answer of 2 pair
{
	return abs(tar.first-tar.second)+1;
}

pair<int,int> TryOdd(int const & index) //try odd string 
{
	int p1=index,p2=index;
	while(p1-1>=0 && p2+1<n && s[p1-1]==s[p2+1])
	{
		p1--,p2++;
	}
	return make_pair(p1,p2);
}

pair<int,int> TryEven(int const & index) //try even string 
{
	int p1=index,p2=index+1;
	while(p1-1>=0 && p2+1<n  && s[p1-1]==s[p2+1])
	{
		p1--,p2++;
	}
	return make_pair(p1,p2);
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

	//take input
	InputFile>>n;
	InputFile>>s;

	auto started = chrono::high_resolution_clock::now();
	//solve the problem
	pair<int,int> len,New;
	int ans=1,stop=n-1;
	loop(i,1,stop)
	{
		New=TryOdd(i);
		if(CalcLen(New)>ans)
		{
			len=New;
			ans=CalcLen(New);
		}
		New=TryEven(i);
		if(CalcLen(New)>ans)
		{
			len=New;
			ans=CalcLen(New);
		}
	}

	auto done = chrono::high_resolution_clock::now();
	long long timespent=chrono::duration_cast< chrono::milliseconds >(done-started).count();
	//print the output 
	ofstream OutputFile,TimeFile;
	OutputFile.open(argv[2], ios::out);
	TimeFile.open(argv[3], ios::out);
	if (!OutputFile || !TimeFile )
	{
		cout<<"Error can't create file";
		return 1;
	}
	TimeFile << "Running time: " << timespent <<"ms\n";
	OutputFile<<ans<<endl;
	loop(i,len.first,len.second+1)
		OutputFile<<s[i];
	OutputFile<<endl;
	return 0;
}

