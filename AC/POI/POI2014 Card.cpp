#include <bits/stdc++.h>
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
const int inf=0x7fffffff,mod=(int)1e9+7,dxy[]={-1,0,1,0,-1};
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

pii arr[N];

struct Segment_Tree{
	struct Node{
		int L,R,mi[2];
		Node operator +(const Node &rhs)const{
			Node res;
			res.L=L,res.R=rhs.R;
			res.mi[0]=res.mi[1]=inf;
			if(mi[0]<=arr[rhs.L].fi)Min(res.mi[0],rhs.mi[0]);
			if(mi[0]<=arr[rhs.L].se)Min(res.mi[0],rhs.mi[1]);
			if(mi[1]<=arr[rhs.L].fi)Min(res.mi[1],rhs.mi[0]);
			if(mi[1]<=arr[rhs.L].se)Min(res.mi[1],rhs.mi[1]);
			return res;
		}
	}tree[N<<2];
	
	void cons(int L,int R,int k=1){
		tree[k].L=L,tree[k].R=R;
		if(L==R){
			tree[k].mi[0]=arr[L].fi,tree[k].mi[1]=arr[L].se;
			return;
		}
		int mid=L+R>>1;
		cons(L,mid,lson);
		cons(mid+1,R,rson);
		tree[k]=tree[lson]+tree[rson];
	}
	void modify(int tar,int k=1){
		if(tree[k].L==tree[k].R){
			tree[k].mi[0]=arr[tree[k].L].fi,tree[k].mi[1]=arr[tree[k].L].se;
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		if(tar<=mid)modify(tar,lson);
		else modify(tar,rson);
		tree[k]=tree[lson]+tree[rson];
	}
	inline bool query(){
		return tree[1].mi[0]<inf||tree[1].mi[1]<inf;
	}
}smt;

int main(){
	int n,m;
	rd(n);
	rep(i,1,n+1)rd(arr[i].fi),rd(arr[i].se);
	smt.cons(1,n);
	rd(m);
	for(int a,b;m--;puts(smt.query()?"TAK":"NIE")){
		rd(a),rd(b);
		if(a==b)continue;
		swap(arr[a],arr[b]);
		smt.modify(a);
		smt.modify(b);
	}
	return 0;
}

/*
	
	Oct.06.16
	
	Tags:segment tree
	Submissions:1
	
	Memory 15764KB
	Time 1852MS
	Code Length 3237B
	
*/

