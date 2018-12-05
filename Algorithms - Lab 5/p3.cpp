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

const int N = 1000;
ll dp[N][N];
int arr[N];
int n;

long long solve(int i, int j) 
{
	if (i > j) 
		return 0;
	ll& ret = dp[i][j];
	if (ret!=-1) 
		return ret;
	return ret = max(arr[i] + min(solve(i + 1, j - 1), solve(i + 2, j)), arr[j] + min(solve(i + 1, j - 1), solve(i, j - 2)));
}



void getPath(int i, int j) 
{
	if (i > j) return;
	ll path1 = min(solve(i + 1, j - 1), solve(i + 2, j));
	ll path2 = min(solve(i + 1, j - 1), solve(i, j - 2));
	if (arr[i] + path1 == dp[i][j]) 
	{
		printf("Player 1: \"Please, choose a coin\": %d \n",arr[i]);
		if (path1 == solve(i + 1, j - 1)) 
		{
			printf("Player 2: \"Please, choose a coin\":  %d \n",arr[j]);
			getPath(i + 1, j - 1);
		}
		else 
		{
			printf("Player 2: \"Please, choose a coin\":  %d \n",arr[i+1]);
			getPath(i + 2, j);
		}
	}
	else 
	{
		printf("Player 1: \"Please, choose a coin\": %d \n",arr[j]);
		if (path2 == solve(i + 1, j - 1)) 
		{
			printf("Player 2: \"Please, choose a coin\":  %d \n",arr[i]);
			getPath(i + 1, j - 1);
		}
		else 
		{
			printf("Player 2: \"Please, choose a coin\":  %d \n",arr[j-1]);
			getPath(i, j - 2);
		}
	}
}


int main()
{
	//init();
	mem(dp, -1);
	cin >> n;
	lop(i,n)
		cin >> arr[i];
	ll ans = solve(0, n - 1);
	getPath(0, n - 1);
	printf("\"GAME OVER!\", Player 1 wins with score %lld\n", ans);

	return 0;
}