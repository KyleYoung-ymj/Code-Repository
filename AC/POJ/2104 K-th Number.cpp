#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5,LG=20;
int tot,num[N],mp[N],Ttree[N*LG],Lson[N*LG],Rson[N*LG],sum[N*LG];
struct Chairman_Tree{
	inline void init(){
		tot=0;
	}
	void build(int L,int R,int &tid){
		tid=++tot;
		sum[tid]=0;
		if(L==R)return;
		int mid=L+R>>1;
		build(L,mid,Lson[tid]);
		build(mid+1,R,Rson[tid]);
	}
	void insert(int oid,int L,int R,int x,int &tid){
		tid=++tot;
		Lson[tid]=Lson[oid];
		Rson[tid]=Rson[oid];
		sum[tid]=sum[oid]+1;
		if(L==R)return;
		int mid=L+R>>1;
		if(x<=mid)insert(Lson[oid],L,mid,x,Lson[tid]);
		else insert(Rson[oid],mid+1,R,x,Rson[tid]);
	}
	int solve(int Lt,int Rt,int L,int R,int k){
		if(L==R)return L;
		int mid=L+R>>1,cnt=sum[Lson[Rt]]-sum[Lson[Lt]];
		if(cnt>=k)return solve(Lson[Lt],Lson[Rt],L,mid,k);
		return solve(Rson[Lt],Rson[Rt],mid+1,R,k-cnt);
	}
}T;
int main(){
	int n,m,L,R,k;
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;++i){
			scanf("%d",&num[i]);
			mp[i]=num[i];
		}
		sort(mp+1,mp+n+1);
		int cnt=unique(mp+1,mp+n+1)-mp-1;
		T.init();
		T.build(1,cnt,Ttree[0]);
		for(int i=1;i<=n;++i){
			num[i]=lower_bound(mp+1,mp+cnt+1,num[i])-mp;
			T.insert(Ttree[i-1],1,cnt,num[i],Ttree[i]);
		}
		while(m--&&scanf("%d%d%d",&L,&R,&k))
			printf("%d\n",mp[T.solve(Ttree[L-1],Ttree[R],1,cnt,k)]);
	}
	return 0;
}
/*
	
	Feb.04.16
	
	Tags:Data Structure,classic
	Submissions:2
	
	Memory 24508K
	Time 1547MS
	Code Length 1311B
	
*/
