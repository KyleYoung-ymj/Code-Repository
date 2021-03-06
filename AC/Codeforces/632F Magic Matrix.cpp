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
const int N=2505;
int n,num[N][N];
piii dat[N*N];
bitset<N>bs[N];
bool solve(){
	int tot=0;
	for(int i=0;i<n;++i){
		if(num[i][i])return false;
		for(int j=0;j<n;++j){
			if(num[i][j]!=num[j][i])return false;
			dat[tot++]=piii(num[i][j],pii(i,j));
		}
	}
	sort(dat,dat+tot);
	for(int i=0,j=0;i<tot;i=j){
		for(++j;j<tot&&dat[j].fi==dat[i].fi;++j);
		for(int k=i;k<j;++k){
			pii P=dat[k].se;
			if((bs[P.fi]&bs[P.se]).any())return false;
		}
		for(int k=i;k<j;++k){
			pii P=dat[k].se;
			bs[P.fi][P.se]=true;
		}
	}
}
int main(){
	rd(n);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			rd(num[i][j]);
	puts(solve()?"MAGIC":"NOT MAGIC");
	return 0;
}
/*
	
	Jul.12.16

	Tags:bitset
	Submissions:1

	Time 2277ms
	Memory 99000KB

*/
