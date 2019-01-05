#include <bits/stdc++.h>

using namespace std;

#define lop(i,n) for(int i=0; i<n; i++)
#define loop(i,start,n) for(int i=start; i<n; i++)


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
	int n, m;
	InputFile >> n >> m;
	vector<vector<int>> adj(n);
	vector<int> Color(n, -1);
	vector<bool> Empty(n);
	lop(i,m) 
	{
		int fir,sec;
		InputFile >> fir >> sec;
		adj[fir].push_back(sec);
		adj[sec].push_back(fir);
	}

	auto started = chrono::high_resolution_clock::now();
	//solve the problem
	Color[0] = 0;
	loop(iter,1,n) 
	{
		fill(Empty.begin(), Empty.end(), true);
		lop(i,adj[iter].size())
		{
			if (Color[ adj[iter][i] ] != -1)
			{
				Empty[Color[ adj[iter][i] ]] = false;
			}
		}
		lop(i,n)
		{
			if (Empty[i]) 
			{
				Color[iter] = i;
				break;
			}
		}
	}
	auto done = chrono::high_resolution_clock::now();
	long long timespent=chrono::duration_cast< chrono::milliseconds >(done-started).count();
	//print the result 
	ofstream OutputFile,TimeFile;
	OutputFile.open(argv[2], ios::out);
	TimeFile.open(argv[3], ios::out);
	if (!OutputFile || !TimeFile )
	{
		cout<<"Error can't create file";
		return 1;
	}
	cout<<"here";
	TimeFile << "Running time: " << timespent <<"ms\n";
	lop(i,n)
		OutputFile << i << ' ' << Color[i] << endl;
	return 0;
}


