//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iterator>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <sstream>
#include <memory.h>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <valarray>
#include <fstream>
#include <functional>
#include <utility>
#include <numeric>
#include <chrono>


using namespace std;
typedef short int sh;
typedef unsigned short int ush;
typedef long long ll;
typedef unsigned long long ull;


#define ii pair<int, int>
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define lop(i,n) for(int i=0; i<n; i++)
#define rlop(i,n) for(int i=n-1; i>=0; i--)
#define loop(i,start,n) for(int i=start; i<n; i++)
#define rloop(i,end,n) for(int i=n-1; i>=end; i--)
#define in1(u) ll u; cin>>u;
#define in2(u,x) ll u,x; cin>>u>>x;
#define inc(u) char u; cin>>u;
#define ins(u) string u; cin>>u;
#define sc(u) scanf(" %I64d",&u);
#define sc2(u,x) scanf("%lld %lld",&u,&x);
#define pr(u) printf("%d",u);
#define mem(u,x) memset(u,x,sizeof(u));
#define PI 3.14159265

int const diff = 'a' - 'A';
sh const soo = 32767;
int const oo = 2147483647;
ll const loo = 9223372036854775807;
int dx[] = { 0,0,1,-1,1,1,-1,-1 };
int dy[] = { 1,-1,0,0,-1,1,1,-1 };
int amod(int a, int b) {return (a % b + b) % b;}
int const MOD=998244353;

int gcd(int u, int v)
{
	if(v==0)
		return u;
	return gcd(v,u%v);
}


/*
int row,col;
bool ill(int i, int j)
{
return (i > -1 && j > -1 && j < row && i < col);
}*/

ll Mpow(ll base,int power)
{
	if(power<1) return 1;
	ll sqrt= Mpow(base,power>>1)%MOD;
	sqrt=(sqrt*sqrt)%MOD;
	if(power&1)
		return (sqrt*base)%MOD;
	return sqrt;
}

void init()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	freopen("words20K.txt","r",stdin);
	freopen("output.txt","w",stdout);
}


string arr[20000];
int timer[20000];
string Mhash[24000];
int val[4]={39,392 ,393,394 };

int cal(int index)
{
	int end=min(int(arr[index].size()),4);
	int x=0;
	lop(i,end)
		x+=(val[i]*int(arr[index][i]));

	return x%24000;

}

int main()
{
	init();
	lop(i,20000)
		cin>>arr[i];

	lop(i,24000)
		Mhash[i]="";
	cout<<"part C: time for each 500\n";

	lop(i,20000)
	{
		auto started = chrono::high_resolution_clock::now(); //start time 
		int newindex=cal(i);
		while(Mhash[newindex]!="")
			newindex=(newindex+1)%24000;
		Mhash[newindex]=arr[i];
		auto done = chrono::high_resolution_clock::now();//end time 

		timer[i]=chrono::duration_cast< chrono::milliseconds >(done-started).count();//calculte algoritm time 
		
	}
	ll curr=0;
	lop(i,40)
	{
		int start=500*i,end=start+500;
		loop(j,start,end)
			curr+=timer[j];
		cout<<"for 500 elements #"<<i+1<<"time: "<<curr<<endl;
		curr=0;
	}
	int mn=oo,mx=-1,sum=0;
	vi prob;
	loop(i,14000,15000)
	{
		int counter=0;
		int newindex=cal(i);
		while(Mhash[newindex]!=arr[i] && Mhash[newindex]!="" && counter<24000)
			newindex=(newindex+1)%24000,counter++;
		Mhash[newindex]="-1";
		mn=min(mn,counter),mx=max(mx,counter),sum+=counter;
		prob.push_back(counter);
	}
	float avg=sum/1000.0;
	cout<<"part D :\n";
	cout<<"min="<<mn<<" max="<<mx<<" avg="<<avg;

}