#include<cstdio>
#include<cstring>
#include<cassert>
#include<algorithm>
#define lowbit(x) (x&-x);
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=(int)2e5+5,mod=(int)1e9+7,INF=0x7fffffff;
int n,L[N],R[N],deque[N],pow_2[N];
pii itv[N];
struct Segment_Tree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	struct Node{
		int L,R,Lsh_cnt,sum;
	}tree[N<<2];
	void build(int L=0,int R=n,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].Lsh_cnt=0;
		tree[k].sum=R==n;
		if(L==R)return;
		int mid=L+R>>1;
		build(L,mid,lson);
		build(mid+1,R,rson);
	}
	inline void push_up(int k){
		if((tree[k].sum=tree[lson].sum+tree[rson].sum)>=mod)
			tree[k].sum-=mod;
	}
	inline void mod_Lsh(int &num,int cnt){
		num=1ll*num*pow_2[cnt]%mod;
	}
	void push_down(int k){
		if(!tree[k].Lsh_cnt)return;
		mod_Lsh(tree[lson].sum,tree[k].Lsh_cnt);
		mod_Lsh(tree[rson].sum,tree[k].Lsh_cnt);
		tree[lson].Lsh_cnt+=tree[k].Lsh_cnt;
		tree[rson].Lsh_cnt+=tree[k].Lsh_cnt;
		tree[k].Lsh_cnt=0;
	}
	int query_sum(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].sum;
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query_sum(L,R,lson);
		if(L>mid)return query_sum(L,R,rson);
		int res=query_sum(L,mid,lson)+query_sum(mid+1,R,rson);
		if(res>=mod)res-=mod;
		return res;
	}
	void modify(int tar,int val,int k=1){
		if(tree[k].L==tree[k].R){
			tree[k].sum=val;
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(tar<=mid)modify(tar,val,lson);
		else modify(tar,val,rson);
		push_up(k);
	}
	void Lsh(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			mod_Lsh(tree[k].sum,1);
			++tree[k].Lsh_cnt;
			return;
		}
		push_down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)Lsh(L,R,lson);
		else if(L>mid)Lsh(L,R,rson);
		else{
			Lsh(L,mid,lson);
			Lsh(mid+1,R,rson);
		}
		push_up(k);
	}
}T;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void init(){
	itv[n]=pii(0,0);
	itv[n+1]=pii(INF,INF);
	sort(itv,itv+n+2);
	int head=0,tail=0;
	deque[tail++]=0;
	for(int i=1;i<=n;++i){
		for(int bin_L=i+1,bin_R=n+1;bin_L<=bin_R;){
			int mid=bin_L+bin_R>>1;
			if(itv[mid].fi>itv[i].se){
				R[i]=mid-1;
				bin_R=mid-1;
			}
			else bin_L=mid+1;
		}
		int bin_L=head,bin_R=tail-1,res;
		while(bin_L<=bin_R){
			int mid=bin_L+bin_R>>1;
			if(itv[deque[mid]].se<itv[i].fi){
				res=mid;
				bin_L=mid+1;
			}
			else bin_R=mid-1;
		}
		L[i]=deque[res]+1;
		head=res;
		while(head<tail&&itv[deque[tail-1]].se>=itv[i].se)--tail;
		deque[tail++]=i;
	}
	pow_2[0]=1;
	for(int i=1;i<=n;++i)
		if((pow_2[i]=pow_2[i-1]<<1)>=mod)pow_2[i]-=mod;
}
int main(){
	rd(n);
	for(int i=0;i<n;++i){
		rd(itv[i].fi);
		rd(itv[i].se);
	}
	init();
	T.build();
	for(int i=n;i;--i){
		if(R[i]<n)T.Lsh(R[i]+1,n);
		T.modify(L[i]-1,(1ll*T.query_sum(L[i],R[i])+(T.query_sum(L[i]-1,L[i]-1)<<1))%mod);
	}
	printf("%d\n",T.query_sum(0,0));
	return 0;
}
