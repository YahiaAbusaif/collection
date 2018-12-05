#include <bits/stdc++.h>

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
char Cl[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
int dx[] = { 0,0,1,-1,1,1,-1,-1 };
int dy[] = { 1,-1,0,0,-1,1,1,-1 };
int amod(const int & a,const int & b) {return (a % b + b) % b;}
int const MOD=1000000007;


int n;
int arr[3];
const int N=1000;
int dp[N];


int solve(int rem)
{
	if(rem<0)
		return -10000;
	if(rem==0)
		return 0;
	if(dp[rem]!=oo)
		return dp[rem];
	return dp[rem]=max(max(solve(rem-arr[0])+1,solve(rem-arr[1])+1),solve(rem-arr[2])+1);

}
int main()
{
	for(int i=0;i<N;i++)
		dp[i]=oo;
	cin>>n>>arr[0]>>arr[1]>>arr[2];
	sort(arr,arr+3);
	int ans=solve(n);
	if(ans>0)
		cout<<ans;
	else
		cout<<"No valid answer /n";
	
}