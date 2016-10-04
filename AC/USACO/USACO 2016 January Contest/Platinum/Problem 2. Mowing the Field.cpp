#include<cstdio>
#include<algorithm>
#define fi first
#define se second
#define lowbit(x) (x&-x)
using namespace std;
typedef pair<int,int> Point;
const int N=(int)1e5+5,MAX_VAL=(int)1e9;
int n;
Point point[N];
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
struct Node{
	int val;
	Node *ch[2];
	Node(){
		val=0;
		ch[0]=ch[1]=NULL;
	}
	Node* get_child(bool id){
		if(!ch[id])ch[id]=new Node;
		return ch[id];
	}
	int query(int l,int r,int L,int R){
		if(L==l&&R==r)return val;
		int mid=l+r>>1;
		if(R<=mid)return ch[0]?ch[0]->query(l,mid,L,R):0;
		if(L>mid)return ch[1]?ch[1]->query(mid+1,r,L,R):0;
		return (ch[0]?ch[0]->query(l,mid,L,mid):0)+(ch[1]?ch[1]->query(mid+1,r,mid+1,R):0);
	}
	void add(int l,int r,int tar,int v){
		val+=v;
		if(l==r)return;
		int mid=l+r>>1;
		if(tar<=mid)get_child(0)->add(l,mid,tar,v);
		else get_child(1)->add(mid+1,r,tar,v);
	}
}bit[N];
struct Query{
	int y,x_L,x_R,t;
	inline bool operator <(const Query &tmp)const{
		return y<tmp.y;
	}
}query[N];
struct Update{
	int x,y,t,flag;
	inline bool operator <(const Update &tmp)const{
		return y<tmp.y;
	}
}update[N<<1];
void add(int x,int tar,int v){
	for(;x<n;x+=lowbit(x))
		bit[x].add(0,MAX_VAL,tar,v);
}
int sum(int x,int L,int R){
	int res=0;
	for(;x>0;x-=lowbit(x))
		res+=bit[x].query(0,MAX_VAL,L,R);
	return res;
}
int query_sum(int l,int r,int L,int R){
	if(l>r)return 0;
	return sum(r,L,R)-sum(l-1,L,R);
}
int main(){
	freopen("mowing.in","r",stdin);
	freopen("mowing.out","w",stdout);
	int T;
	rd(n);rd(T);
	int cnt_x=0,cnt_y=0;
	for(int i=0;i<n;++i){
		rd(point[i].fi);
		rd(point[i].se);
	}
	int cnt_query=0,cnt_update=0;
	for(int i=1;i<n;++i){
		int cur_x=point[i].fi,
			cur_y=point[i].se,
			pre_x=point[i-1].fi,
			pre_y=point[i-1].se;
		if(cur_x==pre_x){
			if(pre_y>cur_y)swap(pre_y,cur_y);
			update[cnt_update++]=(Update){cur_x,pre_y+1,i,1};
			update[cnt_update++]=(Update){cur_x,cur_y,i,-1};
		}
		else{
			if(pre_x>cur_x)swap(pre_x,cur_x);
			query[cnt_query++]=(Query){cur_y,pre_x,cur_x,i};
		}
	}
	sort(query,query+cnt_query);
	sort(update,update+cnt_update);
	int ans=0;
	for(int i=0,j=0;i<cnt_query;++i){
		while(j<cnt_update&&update[j].y<=query[i].y){
			add(update[j].t,update[j].x,update[j].flag);
			++j;
		}
		if(query[i].x_L<query[i].x_R-1){
			ans+=sum(query[i].t-T,query[i].x_L+1,query[i].x_R-1);
			ans+=query_sum(query[i].t+T,n-1,query[i].x_L+1,query[i].x_R-1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
	
	Jul.06.16

	Tags:Data Structure

*/