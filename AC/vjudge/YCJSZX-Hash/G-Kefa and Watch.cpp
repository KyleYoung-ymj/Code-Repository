#include<cstdio>
#include<cstring>
typedef unsigned long long ull;
const int N=1e5+5,P=1e9+7;
const ull B=1e4+7;
int n;
char str[N];
struct Pair{
	ull x;
	int y;
	Pair operator +(const Pair &tmp)const{
		Pair res;
		res.x=x+tmp.x;
		res.y=(1ull*y+tmp.y)%P;
		return res;
	}
	Pair operator *(const ull &tmp)const{
		Pair res;
		res.x=x*tmp;
		res.y=y*tmp%P;
		return res;
	}
	Pair operator *(const Pair &tmp)const{
		Pair res;
		res.x=x*tmp.x;
		res.y=1ull*y*tmp.y%P;
		return res;
	}
	inline bool operator ==(const Pair &tmp)const{
		return x==tmp.x&&y==tmp.y;
	}
};
Pair pow_B[N],sum_pow_B[N];
void pre_pro(){
	sum_pow_B[0]=pow_B[0]=(Pair){1,1};
	for(int i=1;i<n;++i){
		pow_B[i]=pow_B[i-1]*B;
		sum_pow_B[i]=pow_B[i]+sum_pow_B[i-1];
	}
}
struct Segment_Tree{
	struct node{
		int L,R,extra;
		Pair Hash;
	}tree[N<<2];
	void up(int k){
		int mid=tree[k].L+tree[k].R>>1;
		tree[k].Hash=tree[k<<1].Hash*pow_B[tree[k].R-mid]+tree[k<<1|1].Hash;
	}
	void down(int k){
		if(!tree[k].extra)return;
		int mid=tree[k].L+tree[k].R>>1;
		tree[k<<1].extra=tree[k<<1|1].extra=tree[k].extra;
		tree[k<<1].Hash=sum_pow_B[mid-tree[k].L]*tree[k].extra;
		tree[k<<1|1].Hash=sum_pow_B[tree[k].R-mid-1]*tree[k].extra;
		tree[k].extra=0;
	}
	void build(int L,int R,int k){
		tree[k].L=L;
		tree[k].R=R;
		tree[k].extra=0;
		if(L==R){
			tree[k].Hash.x=tree[k].Hash.y=str[L];
			return;
		}
		int mid=L+R>>1;
		build(L,mid,k<<1);
		build(mid+1,R,k<<1|1);
		up(k);
	}
	void update(int L,int R,int x,int k){
		if(tree[k].L==L&&tree[k].R==R){
			tree[k].Hash.x=x*sum_pow_B[R-L].x;
			tree[k].Hash.y=1ull*x*sum_pow_B[R-L].y%P;
			tree[k].extra=x;
			return;
		}
		down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)update(L,R,x,k<<1);
		else if(L>mid)update(L,R,x,k<<1|1);
		else{
			update(L,mid,x,k<<1);
			update(mid+1,R,x,k<<1|1);
		}
		up(k);
	}
	Pair query(int L,int R,int k){
		if(tree[k].L==L&&tree[k].R==R)
			return tree[k].Hash;
		down(k);
		int mid=tree[k].L+tree[k].R>>1;
		if(R<=mid)return query(L,R,k<<1);
		if(L>mid)return query(L,R,k<<1|1);
		return query(L,mid,k<<1)*pow_B[R-mid]+query(mid+1,R,k<<1|1);
	}
	void judge(int L,int R,int t){
		if(L==R||t==R-L+1){
			puts("YES");
			return;
		}
		puts(query(L,R-t,1)==query(L+t,R,1)?"YES":"NO");
	}
}T;
int main(){
	int m,k;
	scanf("%d%d%d%s",&n,&m,&k,str);
	pre_pro();
	T.build(0,n-1,1);
	int tot=m+k,ope,a,b,c;
	while(tot--&&scanf("%d%d%d%d",&ope,&a,&b,&c))
		if(ope==1)T.update(a-1,b-1,c+'0',1);
		else T.judge(a-1,b-1,c);
	return 0;
}
/*
	
	Origin:CodeForces 580E
	Tags:Hash,Dada Structure,Segment Tree,String
	
	Dec.03.15
	Submit:12
	
	Memory 15564KB
	Time 218ms
	Code Length 2480B
	
*/
