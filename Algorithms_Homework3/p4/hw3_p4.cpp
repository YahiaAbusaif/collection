#include <bits/stdc++.h>

using namespace std;
#define lop(i,n) for(int i=0; i<n; i++)


vector<long long> Coin; //value for each coin
vector<vector<long long>> dp; // dp array for store the result of the state

long long solve(int left, int right) 
{
	if (left > right) 
		return 0;
	long long& ret = dp[left][right];
	if (ret!=-1) 
		return ret;
	ret = max(Coin[left] + min(solve(left + 1, right - 1), solve(left + 2, right)), Coin[right] + min(solve(left + 1, right - 1), solve(left, right - 2)));
	return ret;
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
	//take input & initialize the program 
	int n;
	InputFile>>n;
	Coin.resize(n);
	dp.resize(n, vector<long long>(n, -1));
	lop(i,n)
		InputFile>>Coin[i];
	auto started = chrono::high_resolution_clock::now();
	//solve the problem
	long long ans=solve(0,n-1);

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
	return 0;
}

