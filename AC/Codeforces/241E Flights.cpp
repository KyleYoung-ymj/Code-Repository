#include <cstdio>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
const int N=(int)1e3+5,M=(int)5e3+5;
int n,m,dist[N];
bool mark[N],flag[N];
pii es[M];
vector<int>rG[N];
bool Bellman_Ford(){
	for(int i=1;i<n;++i){
		for(int j=0;j<m;++j){
			if(!mark[es[j].fi]||!flag[es[j].se])continue;
			Max(dist[es[j].se],dist[es[j].fi]+1);
			Max(dist[es[j].fi],dist[es[j].se]-2);
		}
	}
	for(int i=0;i<m;++i){
		if(!mark[es[i].fi]||!flag[es[i].se])continue;
		if(dist[es[i].fi]+1>dist[es[i].se])return false;
		if(dist[es[i].se]-2>dist[es[i].fi])return false;
	}
	return true;
}
int main(){
	rd(n);rd(m);
	for(int i=0;i<m;++i){
		rd(es[i].fi);rd(es[i].se);
		rG[es[i].se].push_back(es[i].fi);
	}
	mark[1]=flag[n]=true;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j){
			mark[es[j].se]|=mark[es[j].fi];
			flag[es[j].fi]|=flag[es[j].se];
		}
	if(!Bellman_Ford())return puts("No");
	puts("Yes");
	for(int i=0;i<m;++i){
		if(!mark[es[i].fi]||!flag[es[i].se])puts("1");
		else printf("%d\n",dist[es[i].se]-dist[es[i].fi]);
	}
	return 0;
}
/*
	
	Jul.12.16

	Tags:system of difference constraints
	Submissions:3

	Time 62ms
	Memory 100KB

*/
