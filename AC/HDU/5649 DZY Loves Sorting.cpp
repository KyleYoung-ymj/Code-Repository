#include<cstdio>
const int N=1e5+5;
int n,m,K,num[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
struct Ope{
	int type,L,R;
	inline void Rd(){
		rd(type);rd(L);rd(R);
	}
}ope[N];
struct Segment_Tree{
	struct Node{
		int L,R,sum,same;
		inline int len(){
			return R-L+1;
		}
	}tree[N<<2];
	inline void push_up(int k){
		tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
	}
	void push_down(int k){
		if(tree[k].same==-1)return;
		tree[k<<1].same=tree[k<<1|1].same=tree[k].same;
		tree[k<<1].sum=tree[k].same*tree[k<<1].len();
		tree[k<<1|1].sum=tree[k].same*tree[k<<1|1].len();
		tree[k].same=-1;
	}
	void construct(int L,int R,int val,int k=1){
		tree[k]=(Node){L,R,0,-1};
		if(L==R){
			tree[k].sum=num[L]>val;
			return;
		}
		int mid=L+R>>1;
		construct(L,mid,val,k<<1);
		construct(mid+1,R,val,k<<1|1);
		push_up(k);
	}
	void update(int L,int R,bool val,int k=1){
		if(L>R)return;
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].sum=val*tree[k].len();
			tree[k].same=val;
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)update(L,R,val,k<<1);
		else if(L>mid)update(L,R,val,k<<1|1);
		else{
			update(L,mid,val,k<<1);
			update(mid+1,R,val,k<<1|1);
		}
		push_up(k);
	}
	int query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].sum;
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return query(L,mid,k<<1)+query(mid+1,R,k<<1|1);
	}
}T;
bool judge(int val){
	T.construct(1,n,val);
	for(int i=0;i<m;++i){
		int L=ope[i].L,R=ope[i].R,amt=T.query(L,R);
		if(ope[i].type){
			T.update(L,L+amt-1,1);
			T.update(L+amt,R,0);
		}
		else{
			T.update(L,R-amt,0);
			T.update(R-amt+1,R,1);
		}
	}
	return !T.query(K,K);
}
void solve(){
	rd(n);rd(m);
	for(int i=1;i<=n;++i)
		rd(num[i]);
	for(int i=0;i<m;++i)
		ope[i].Rd();
	rd(K);
	int L=1,R=n,ans;
	while(L<=R){
		int mid=L+R>>1;
		if(judge(mid)){
			ans=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	printf("%d\n",ans);
}
int main(){
	int cas;
	rd(cas);
	while(cas--)solve();
	return 0;
}
/*
	
	May.27.16
	
	Tags:binary search,Segment Tree
	Submissions:2
	
	Exe.Time 2043MS
	Exe.Memory 3044K
	Code Len. 2245B
	
*/
