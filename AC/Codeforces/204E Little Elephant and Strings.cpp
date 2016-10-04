#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define y1 jfskav
#define pb push_back
#define lson (k<<1)
#define rson (k<<1|1)
#define lowbit(x) ((x)&-(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define rep(i,s,t) for(register int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(register int i=(t)-1,_s=(s);i>=_s;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;
const int mod=(int)1e9+7,inf=0x7fffffff,dxy[]={-1,0,1,0,-1};
const ll INF=1ll<<60;
const db pi=acos(-1),eps=1e-6;
template<class T>void rd(T &x){
	x=0;
	char c;
	while(c=getchar(),c<48);
	do x=(x<<3)+(x<<1)+(c^48);
		while(c=getchar(),c>47);
}
template<class T>void rec_pt(T x){
	if(!x)return;
	rec_pt(x/10);
	putchar(x%10^48);
}
template<class T>void pt(T x){
	if(!x)putchar('0');
	else rec_pt(x);
}
template<class T>inline void ptn(T x){
	pt(x),putchar('\n');
}
template<class T>inline void Max(T &a,T b){
	if(b>a)a=b;
}
template<class T>inline void Min(T &a,T b){
	if(b<a)a=b;
}
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
inline void mod_add(int &a,int b,int m=mod){
	if((a+=b)>=m)a-=m;
}
inline void mod_minus(int &a,int b,int m=mod){
	if((a-=b)<0)a+=m;
}
int mod_pow(int a,int b,int m=mod){
	int res=1;
	for(;b;b>>=1,a=(ll)a*a%m)
		if(b&1)res=(ll)res*a%m;
	return res;
}
inline int calc_inv(int x,int m=mod){
	return mod_pow(x,m-2);
}


const int N=(int)2e5+5;

char str[N],sub[(int)1e5+5];

// Suffix Automaton
const int NODE=N<<1,C=27;

int allc,last,par[NODE],len[NODE],trans[NODE][C],mx[NODE];

void extend(int c,int id){
	int np=++allc,p=last;
	len[np]=len[last]+1;
	mx[np]=id;
	for(;p&&!trans[p][c];p=par[p])trans[p][c]=np;
	if(!p)par[np]=1;
	else{
		int q=trans[p][c];
		if(len[q]==len[p]+1)par[np]=q;
		else{
			int nq=++allc;
			par[nq]=par[q];
			len[nq]=len[p]+1;
			mx[nq]=min(mx[q],len[nq]);
			memcpy(trans[nq],trans[q],C<<2);
			par[np]=par[q]=nq;
			for(trans[p][c]=nq,p=par[p];p&&trans[p][c]==q;p=par[p])trans[p][c]=nq;
		}
	}
	last=np;
}
void cons(int n){
	last=++allc;
	for(int i=0,id=1;i<n;++i,++id){
		if(str[i]==26)id=0;
		extend(str[i],id);
	}
}

int m,tot_edge,head[NODE],sz[NODE],heavy_son[NODE],top[NODE],allc_tid,tid[NODE];
ll sum[NODE];
pii edge[NODE];

void add_edge(int u,int v){
	edge[tot_edge]=pii(v,head[u]);
	head[u]=tot_edge++;
}
void dfs(int cur){
	sz[cur]=1;
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		dfs(son);
		sz[cur]+=sz[son];
		if(sz[son]>sz[heavy_son[cur]])heavy_son[cur]=son;
	}
}
void allc_dfs(int cur,int anc){
	if(!cur)return;
	top[cur]=anc;
	tid[cur]=++allc_tid;
	allc_dfs(heavy_son[cur],anc);
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		if(son==heavy_son[cur])continue;
		allc_dfs(son,son);
	}
}

int bit[NODE];

void add(int x,int v){
	for(;x;x-=lowbit(x))
		bit[x]+=v;
}
inline void add_itv(int L,int R){
	add(L-1,-1),add(R,1);
}
int query(int x){
	int res=0;
	for(;x<=allc;x+=lowbit(x))
		res+=bit[x];
	return res;
}

struct Node{
	int L,R,mx,pos;
	bool tag;
	Node operator +(const Node &rhs)const{
		Node res;
		res.L=L,res.R=rhs.R;
		res.mx=mx;
		if(rhs.mx==mx)res.pos=rhs.pos;
		else res.pos=pos;
		res.tag=false;
		return res;
	}
}tree[NODE<<2];

struct Segment_Tree{
	void push_down(int k){
		if(!tree[k].tag)return;
		tree[lson].mx=tree[rson].mx=tree[k].mx;
		tree[lson].pos=tree[k].L+tree[k].R>>1;
		tree[rson].pos=tree[k].R;
		tree[lson].tag=tree[rson].tag=true;
		tree[k].tag=false;
	}
	void cons(int L,int R,int k=1){
		if(L==R){
			tree[k].L=tree[k].R=L;
			tree[k].mx=0;
			tree[k].pos=L;
			tree[k].tag=false;
			return;
		}
		int mid=L+R>>1;
		cons(L,mid,lson);
		cons(mid+1,R,rson);
		tree[k]=tree[lson]+tree[rson];
	}
	Node query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)return tree[k];
		int mid=tree[k].L+tree[k].R>>1;
		push_down(k);
		if(R<=mid)return query(L,R,lson);
		if(L>mid)return query(L,R,rson);
		return query(L,mid,lson)+query(mid+1,R,rson);
	}
	void modify(int L,int R,int val,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].mx=val;
			tree[k].pos=R;
			tree[k].tag=true;
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		push_down(k);
		if(R<=mid)modify(L,R,val,lson);
		else if(L>mid)modify(L,R,val,rson);
		else{
			modify(L,mid,val,lson);
			modify(mid+1,R,val,rson);
		}
		tree[k]=tree[lson]+tree[rson];
	}
}T;

void update(int cur,int id){
	for(;top[cur]>1;cur=par[top[cur]]){
		Node tmp=T.query(tid[top[cur]],tid[cur]);
		if(tmp.mx==id){
			if(tmp.pos<tid[cur]){
				add_itv(tmp.pos+1,tid[cur]);
				T.modify(tmp.pos+1,tid[cur],id);
			}
			return;
		}
		add_itv(tid[top[cur]],tid[cur]);
		T.modify(tid[top[cur]],tid[cur],id);
	}
	Node tmp=T.query(1,tid[cur]);
	if(tmp.mx==id){
		if(tmp.pos<tid[cur]){
			add_itv(tmp.pos+1,tid[cur]);
			T.modify(tmp.pos+1,tid[cur],id);
		}
		return;
	}
	add(tid[cur],1);
	T.modify(1,tid[cur],id);
}

void DP(int cur){
	if(cur>1&&query(tid[cur])>=m)sum[cur]+=mx[cur]-len[par[cur]];
	for(int i=head[cur];~i;i=edge[i].se){
		int son=edge[i].fi;
		sum[son]=sum[cur];
		DP(son);
	}
}

int main(){
	int n;
	rd(n),rd(m);
	int len=0;
	rep(i,0,n){
		scanf("%s",sub);
		rep(j,0,strlen(sub))str[len++]=sub[j]-'a';
		str[len++]=26;
	}
	cons(len);
	memset(head,-1,allc+1<<2);
	rep(i,2,allc+1)add_edge(par[i],i);
	dfs(1);
	allc_dfs(1,1);
	T.cons(1,allc);
	for(int i=0,cur=1,id=1;i<len;++i){
		if(str[i]==26){
			cur=1;
			++id;
			continue;
		}
		update(cur=trans[cur][str[i]],id);
	}
	DP(1);
	ll ans=0;
	for(int i=0,cnt=0,cur=1;;++i){
		if(str[i]==26){
			pt(ans);
			putchar(' ');
			if(++cnt==n){
				putchar('\n');
				return 0;
			}
			ans=0;
			cur=1;
			continue;
		}
		ans+=sum[cur=trans[cur][str[i]]];
	}
}

/*
	
	Sept.11.16

	Tags:string,SAM,tree,HLD,data structure,segment tree
	Submissions:4

	Time 810ms
	Memory 97248KB
	
*/
