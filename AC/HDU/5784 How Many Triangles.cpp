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
#define pb push_back
#define y1 kjfasiv
#define lowbit(x) (x&-x)
#define debug(x) cout<<#x<<"="<<x<<endl
#define lson (k<<1)
#define rson (k<<1|1)
#define Debug(x) cout<<endl<<#x<<"="<<x<<"!!!!!"<<endl<<endl
#define rep(i,s,t) for(int i=s,_t=t;i<t;++i)
#define per(i,s,t) for(int i=t-1,_s=s;i>=_s;--i)
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
typedef complex<db> Com;
const int mod=(int)1e9+7,inf=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_print(T x){
	if(!x)return;
	rec_print(x/10);
	putchar(x%10^48);
}
template<class T>void print(T x){
	if(!x)putchar('0');
	else rec_print(x);
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
int fast_mod_pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)res=1ll*res*a%mod;
	return res;
}

struct Point{
	int x,y,qua;
	Point(int xx=0,int yy=0){
		x=xx,y=yy;
		if(x>0&&y>=0)qua=1;
		else if(x<=0&&y>0)qua=2;
		else if(x<0&&y<=0)qua=3;
		else if(x>=0&&y<0)qua=4;
	}
	inline void Rd(){
		rd(x),rd(y);
	}
};
typedef Point Vec;
Vec operator -(Point a,Point b){
	return Vec(a.x-b.x,a.y-b.y);
}
ll Dot(Vec a,Vec b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}
ll Cross(Vec a,Vec b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}
bool polar_cmp(Vec a,Vec b){
//	return atan2(a.y,a.x)<atan2(b.y,b.x);
	if(a.qua!=b.qua)return a.qua<b.qua;
	return Cross(a,b)>0;
}

const int N=(int)2e3+5;
int n;
Point point[N];
Vec arr[N<<1];
void solve(){
	rep(i,0,n)point[i].Rd();
	int m=n-1;
	ll acute=0,right_obtuse=0;
	rep(i,0,n){
		for(int j=0,cnt=0;j<n;++j){
			if(i==j)continue;
			arr[cnt++]=point[j]-point[i];
		}
		sort(arr,arr+m,polar_cmp);
		rep(j,0,m)arr[j+m]=arr[j];
//		rep(j,0,m<<1)debug(arr[j].x),debug(arr[j].y);//
		for(int j=0,k=0,t=0,s=0;j<m;++j){
			for(;k<j+m&&!Cross(arr[j],arr[k])&&Dot(arr[j],arr[k])>0;++k);
			for(Max(t,k);t<j+m&&Cross(arr[j],arr[t])>0&&Dot(arr[j],arr[t])>0;++t);
			for(Max(s,t);s<j+m&&Cross(arr[j],arr[s])>0&&Dot(arr[j],arr[s])<0;++s);
//			debug(k),debug(t),debug(s);//
			acute+=t-k;
			right_obtuse+=s-t;
		}
	}
//	debug(acute),debug(right_obtuse);//
	print((acute-(right_obtuse<<1))/3);
	putchar('\n');
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Aug.03.16
	
	Tags:polar sort,two pointers
	
	Time 2823ms
	Memory 1664K
	Code Len. 3117B
	
*/

