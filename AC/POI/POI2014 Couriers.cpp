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
 
 
const int N=(int)5e5+5;

int arr[N];
veci pos[N];

struct Segment_Tree{
	struct Node{
		int L,R,val,cnt;
		Node operator +(const Node &rhs)const{
			Node res;
			res.L=L,res.R=rhs.R;
			if(val==rhs.val)res.val=val,res.cnt=cnt+rhs.cnt;
			else if(cnt>rhs.cnt)res.val=val,res.cnt=cnt-rhs.cnt;
			else res.val=rhs.val,res.cnt=rhs.cnt-cnt;
			return res;
		}
	}tree[N<<2];
	void cons(int L,int R,int k=1){
		tree[k].L=L,tree[k].R=R;
		if(L==R){
			tree[k].val=arr[L],tree[k].cnt=1;
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
		if(R<=mid)return query(L,R,lson);
		if(L>mid)return query(L,R,rson);
		return query(L,mid,lson)+query(mid+1,R,rson);
	}
}smt;

inline int query_cnt(int tar,int L,int R){
	return upper_bound(pos[tar].begin(),pos[tar].end(),R)-lower_bound(pos[tar].begin(),pos[tar].end(),L);
}

int main(){
	int n,m;
	rd(n),rd(m);
	rep(i,1,n+1){
		rd(arr[i]);
		pos[arr[i]].pb(i);
	}
	smt.cons(1,n);
	for(int L,R;m--;){
		rd(L),rd(R);
		int ans=smt.query(L,R).val;
		ptn(query_cnt(ans,L,R)>R-L+1>>1?ans:0);
	}
	return 0;
}

/*
	
	Oct.06.16
	
	Tags:segment tree
	Submissions:2
	
	Memory 53360KB
	Time 1612MS
	Code Length 3155B
	
*/

