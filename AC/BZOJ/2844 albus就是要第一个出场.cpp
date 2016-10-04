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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=10086,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
const double pi=acos(-1.0),eps=1e-8;
template<class T>void rd(T &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
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
	for(;b;b>>=1,(a*=a)%=mod)
		if(b&1)(res*=a)%=mod;
	return res;
}
const int N=(int)1e5+5;
int n,cnt_zero,num[N];
void Gauss(){
	int ptr=0;
	for(int mask=1<<30,i;mask;mask>>=1){
		for(i=ptr;i<n;++i)
			if(num[i]&mask)
				break;
		if(i==n)continue;
		swap(num[ptr],num[i]);
		for(i=0;i<n;++i)
			if(i!=ptr&&num[i]&mask)
				num[i]^=num[ptr];
		++ptr;
	}
	cnt_zero=n-ptr;
	n=ptr;
}
int main(){
	rd(n);
	for(int i=0;i<n;++i)
		rd(num[i]);
	int tar;
	rd(tar);
	if(!tar)return puts("1");
	Gauss();
	int ans=0;
	for(int i=0,cur=0;i<n;++i){
		if((cur^num[i])<tar){
			cur^=num[i];
			mod_add(ans,fast_mod_pow(2,n-1-i));
		}
	}
	mod_add(ans,1);
	(ans*=fast_mod_pow(2,cnt_zero))%=mod;
	mod_add(ans,1);
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jul.19.16

	Tags:math,xor,Gauss Elimination
	Submissions:2

	Memory 1684kb
	Time 232ms
	Code Length 2034B

*/
