#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int LEN=2e6+5;
const ull B=1e4+7;
char str[LEN];
ull pow_B[LEN];
set<int>pat;
struct Segment_Tree{
	struct node{
		int L,R,mid;
		ull Hash;
	}tree[LEN<<2];
	inline void up(int k){
		tree[k].Hash=tree[k<<1].Hash*pow_B[tree[k].R-tree[k].mid]+tree[k<<1|1].Hash;
	}
	void build(int L,int R,int k){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].mid=L+R>>1;
		if(L==R){
			tree[k].Hash=str[L];
			return;
		}
		build(L,tree[k].mid,k<<1);
		build(tree[k].mid+1,R,k<<1|1);
		up(k);
	}
	ull query(int L,int R,int k){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].Hash;
		if(R<=tree[k].mid)return query(L,R,k<<1);
		if(L>tree[k].mid)return query(L,R,k<<1|1);
		return query(L,tree[k].mid,k<<1)*pow_B[R-tree[k].mid]+query(tree[k].mid+1,R,k<<1|1);
	}
	void update(int x,char c,int k){
		if(tree[k].L==tree[k].R){
			tree[k].Hash=c;
			return;
		}
		if(x<=tree[k].mid)update(x,c,k<<1);
		else update(x,c,k<<1|1);
		up(k);
	}
}T;
char get_visible(){
	char c;
	while(c=getchar(),isspace(c));
	return c;
}
void pre_pro(){
	pow_B[0]=1;
	for(int i=1;i<LEN;++i)
		pow_B[i]=pow_B[i-1]*B;
}
ull make_Hash(){
	int len=strlen(str);
	ull Hash=0;
	for(int i=0;i<len;++i)
		Hash=Hash*B+str[i];
	return Hash;
}
int main(){
	pre_pro();
	int cas,kase=0,n,len,x,y;
	char c;
	scanf("%d",&cas);
	while(cas--){
		printf("Case #%d:\n",++kase);
		scanf("%d",&n);
		pat.clear();
		while(n--&&scanf("%s",str))
			pat.insert(make_Hash());
		scanf("%s%d",str,&n);
		len=strlen(str);
		T.build(0,len-1,1);
		while(n--){
			c=get_visible();
			if(c=='Q'){
				scanf("%d%d",&x,&y);
				puts(pat.find(T.query(x,y,1))!=pat.end()?"Yes":"No");
			}
			else{
				scanf("%d",&x);
				c=get_visible();
				T.update(x,c,1);
			}
		}
	}
	return 0;
}
/*
	
	Nov.28.15
	Submit:2
	
	Memory 24068KB
	Time 1996ms
	Code Length 1861B
	
*/
