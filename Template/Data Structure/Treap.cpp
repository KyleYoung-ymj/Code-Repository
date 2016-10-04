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
const int mod=(int)1e9+7,INF=0x7fffffff,rx[]={-1,0,1,0},ry[]={0,1,0,-1};
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
struct Treap{
	#define lson (ch[0][cur])
	#define rson (ch[1][cur])
	static const int N=(int)1e5+5;
	int allc,root,ch[2][N],val[N],aux[N],mul[N],sz[N];
	inline void init(){
		sz[allc=root=0]=0;
	}
	void Newnode(int &cur,int v){
		cur=++allc;
		lson=rson=0;
		val[cur]=v;
		aux[cur]=rand();
		sz[cur]=mul[cur]=1;
	}
	inline void push_up(int cur){
		sz[cur]=sz[lson]+sz[rson]+mul[cur];
	}
	void rotate(int &x,bool f){
		int y=ch[f][x];
		ch[f][x]=ch[!f][y];
		ch[!f][y]=x;
		push_up(x);
		push_up(y);
		x=y;
	}
	void ins(int &cur,int num){
		if(!cur)return Newnode(cur,num);
		++sz[cur];
		if(val[cur]==num){
			++mul[cur];
			return;
		}
		bool flag=num>val[cur];
		ins(ch[flag][cur],num);
		if(aux[ch[flag][cur]]<aux[cur])rotate(cur,flag);
	}
	void del(int &cur,int num){
		if(!cur)return;
		if(val[cur]==num){
			if(mul[cur]>1){
				--mul[cur];
				--sz[cur];
				return;
			}
			if(!lson||!rson)cur=lson+rson;
			else{
				rotate(cur,aux[rson]>aux[lson]);
				del(cur,num);
			}
		}
		else{
			del(ch[num>val[cur]][cur],num);
			--sz[cur];
		}
	}
	int query_rank(int num){
		for(int cur=root,res=0;;){
			if(val[cur]>num)cur=lson;
			else if(val[cur]==num)return res+sz[lson]+1;
			else{
				res+=sz[lson]+mul[cur];
				cur=rson;
			}
		}
	}
	int query_num(int K){
		for(int cur=root;;){
			if(sz[lson]>=K)cur=lson;
			else if(sz[lson]+mul[cur]>=K)return val[cur];
			else{
				K-=sz[lson]+mul[cur];
				cur=rson;
			}
		}
	}
	int query_pre(int num){
		for(int cur=root,res;;){
			if(!cur)return res;
			if(val[cur]>=num)cur=lson;
			else{
				res=val[cur];
				cur=rson;
			}
		}
	}
	int query_nxt(int num){
		for(int cur=root,res;;){
			if(!cur)return res;
			if(val[cur]<=num)cur=rson;
			else{
				res=val[cur];
				cur=lson;
			}
		}
	}
}treap;
int main(){
	int n;
	rd(n);
	treap.init();
	for(int ope,x;n--;){
		rd(ope);scanf("%d",&x);
		switch(ope){
			case 1:
				treap.ins(treap.root,x);
				break;
			case 2:
				treap.del(treap.root,x);
				break;
			case 3:
				printf("%d\n",treap.query_rank(x));
				break;
			case 4:
				printf("%d\n",treap.query_num(x));
				break;
			case 5:
				printf("%d\n",treap.query_pre(x));
				break;
			case 6:
				printf("%d\n",treap.query_nxt(x));
				break;
		}
	}
	return 0;
}
