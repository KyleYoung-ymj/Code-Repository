#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5;
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
struct Segment_Tree{
	struct node{
		int L,R,mx;
	}tree[N<<2];
	inline void up(int k){
		tree[k].mx=max(tree[k<<1].mx,tree[k<<1|1].mx);
	}
	void build(int L,int R,int x,int k){
		tree[k].L=L;
		tree[k].R=R;
		if(L==R){
			tree[k].mx=L==x;
			return;
		}
		int mid=L+R>>1;
		build(L,mid,x,k<<1);
		build(mid+1,R,x,k<<1|1);
		up(k);
	}
	void update(int L,int R,int x,int a,int k){
		if(tree[k].L==tree[k].R){
			Max(tree[k].mx,a);
			return;
		}
		int mid=tree[k].L+tree[k].R>>1;
		if(x<=mid)update(L,mid,x,a,k<<1);
		else update(mid+1,R,x,a,k<<1|1);
		up(k);
	}
	int query(int L,int R,int k){
		if(L>R)return 0;
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].mx;
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return max(query(L,mid,k<<1),query(mid+1,R,k<<1|1));
	}
}Tree[4];
int num[N],mp[N];
int main(){
//	freopen("flower.in","r",stdin);
//	freopen("flower.out","w",stdout);
	int n;
	rd(n);
	for(int i=0;i<n;++i){
		rd(num[i]);
		mp[i]=num[i];
	}
	sort(mp,mp+n);
	int en=unique(mp,mp+n)-mp,ans=1,tmp;
	for(int i=0;i<n;++i)
		num[i]=lower_bound(mp,mp+en,num[i])-mp+1;
	for(int i=0;i<4;++i)
		Tree[i].build(1,en,num[0],1);
	for(int i=1;i<n;++i){
		Max(ans,tmp=Tree[1].query(num[i]+1,en,1)+1);
		Tree[0].update(1,en,num[i],tmp,1);
		Max(ans,tmp=Tree[0].query(1,num[i]-1,1)+1);
		Tree[1].update(1,en,num[i],tmp,1);
		Max(ans,tmp=Tree[3].query(1,num[i]-1,1)+1);
		Tree[2].update(1,en,num[i],tmp,1);
		Max(ans,tmp=Tree[2].query(num[i]+1,en,1)+1);
		Tree[3].update(1,en,num[i],tmp,1);
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Nov.01.15
	Score 100
	
	Memory 13904K
	Time 500MS
	Code Length 1.93K
	
*/
