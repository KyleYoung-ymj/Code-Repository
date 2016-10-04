#include<cstdio>
const int N=1e5+5,Z=26;
int cnt[Z];
char str[N];
struct Segment_Tree{
	struct Node{
		int L,R,sum,flag;
		inline int len(){
			return R-L+1;
		}
		inline void set(int x){
			sum=len()*x;
		}
	}tree[N<<2];
	inline int up(int k){
		tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
	}
	void down(int k){
		if(tree[k].flag==-1)return;
		tree[k<<1].flag=tree[k<<1|1].flag=tree[k].flag;
		tree[k<<1].set(tree[k].flag);
		tree[k<<1|1].set(tree[k].flag);
		tree[k].flag=-1;
	}
	void build(int L,int R,int id,int k=1){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].flag=-1;
		if(L==R){
			tree[k].sum=str[L]==id+'a';
			return;
		}
		int mid=L+R>>1;
		build(L,mid,id,k<<1);
		build(mid+1,R,id,k<<1|1);
		up(k);
	}
	int query(int L,int R,int k=1){
		if(tree[k].L==L&&tree[k].R==R)return tree[k].sum;
		down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return query(L,mid,k<<1)+query(mid+1,R,k<<1|1);
	}
	void update(int L,int R,int a,int k=1){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].sum=tree[k].len()*a;
			tree[k].flag=a;
			return;
		}
		down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)update(L,R,a,k<<1);
		else if(L>mid)update(L,R,a,k<<1|1);
		else{
			update(L,mid,a,k<<1);
			update(mid+1,R,a,k<<1|1);
		}
		up(k);
	}
}T[Z];
int main(){
	int n,m,L,R,k;
	scanf("%d%d%s",&n,&m,str+1);
	for(int i=0;i<26;++i)T[i].build(1,n,i);
	while(m--&&scanf("%d%d%d",&L,&R,&k)){
		for(int i=0;i<Z;++i){
			cnt[i]=T[i].query(L,R);
			T[i].update(L,R,0);
		} 
		int st,en,delta;
		if(k){
			st=0;en=26;delta=1;
		}
		else{
			st=25;en=-1;delta=-1;
		}
		for(int i=st;i!=en;i+=delta)
			if(cnt[i]){
				T[i].update(L,L+cnt[i]-1,1);
				L+=cnt[i];
			}
	}
	for(int i=1;i<=n;++i)
		for(int j=0;;++j)
			if(T[j].query(i,i)){
				printf("%c",j+'a');
				break;
			}
	puts("");
	return 0;
}
/*
	
	Feb.07.16
	
	Tags:Data Structure,Segment Tree
	Submissions:1
	
	Time 2401ms
	Memory 162700KB
	
*/
