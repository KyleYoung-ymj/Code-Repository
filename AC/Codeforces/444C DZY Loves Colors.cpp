#include<cstdio>
#include<algorithm>
#define lson (k<<1)
#define rson (k<<1|1)
using namespace std;
const int N=1e5+5;
typedef long long ll;
struct Segment_Tree{
	struct Node{
		int L,R,same;
		ll tag,sum;
		inline int len(){
			return R-L+1;
		}
	}tree[N<<2];
	void build(int L,int R,int k=1){
		tree[k]=(Node){L,R,-1,0,0};
		if(L==R){
			tree[k].same=L;
			return;
		}
		int mid=L+R>>1;
		build(L,mid,lson);
		build(mid+1,R,rson);
	}
	inline void push_up(int k){
		tree[k].sum=tree[lson].sum+tree[rson].sum;
		if(tree[lson].same!=tree[rson].same)tree[k].same=-1;
		else tree[k].same=tree[lson].same;
	}
	void update(int k,ll val,int col){
		tree[k].tag+=val;
		tree[k].sum+=1ll*tree[k].len()*val;
		tree[k].same=col;
	}
	void push_down(int k){
		if(!tree[k].tag)return;
		update(lson,tree[k].tag,tree[k].same);
		update(rson,tree[k].tag,tree[k].same);
		tree[k].tag=0;
	}
	void modify(int L,int R,int val,int k=1){
		if(tree[k].L==L&&tree[k].R==R&&~tree[k].same){
			update(k,abs(val-tree[k].same),val);
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
		push_up(k);
	}
	ll query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].sum;
		int mid=tree[k].L+tree[k].R>>1;
		push_down(k);
		if(R<=mid)return query(L,R,lson);
		if(L>mid)return query(L,R,rson);
		return query(L,mid,lson)+query(mid+1,R,rson);
	}
}T;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
int main(){
	int n,m,ope,L,R,val;
	rd(n);rd(m);
	T.build(1,n);
	while(m--){
		rd(ope);rd(L);rd(R);
		if(ope==1){
			rd(val);
			T.modify(L,R,val);
		}
		else printf("%I64d\n",T.query(L,R));
	}
	return 0;
}
/*
	
	Jun.26.16
	
	Tags:Segment Tree
	Submissions:5
	
	Time 187ms
	Memory 12300KB
	
*/
