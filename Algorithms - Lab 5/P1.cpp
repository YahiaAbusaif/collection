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

const int N=1000;
int main()
{
	int arr[N];
	int n;
	cin>>n;
	lop(i,n)
		cin>>arr[i];
	sort(arr,arr+n);
	vi res;
	int p1=0,p2=n-1;
	while(p1<p2)
	{
		res.push_back(arr[p1]);
		res.push_back(arr[p2]);
		p1++,p2--;
	}
	if(p1==p2)
		res.push_back(arr[p1]);
	int ans=0;
	lop(i,n-1)
		ans+=abs(res[i]-res[i+1]);
	ans+=abs(res[n-1]-res[0]);
	cout<<ans;
}