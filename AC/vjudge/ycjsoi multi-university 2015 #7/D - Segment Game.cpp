#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&-x)
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+5,M=N<<1;
int n,tot,num[M],st[N],L[N],R[N],arr[2][M];
pii ope[N];
void add(int *bit,int x,int val){
	while(x<=tot){
		bit[x]+=val;
		x+=lowbit(x);
	}
}
int sum(int *bit,int x){
	int res=0;
	while(x){
		res+=bit[x];
		x-=lowbit(x);
	}
	return res;
}
int calc(int *bit,int id){
	return sum(bit,tot)-sum(bit,id-1);
}
void solve(){
	tot=0;
	for(int i=0,cnt=0;i<n;++i){
		scanf("%d%d",&ope[i].fi,&ope[i].se);
		if(!ope[i].fi){
			num[tot++]=ope[i].se;
			num[tot++]=++cnt+ope[i].se;
			st[cnt]=ope[i].se;
		}
	}
	sort(num,num+tot);
	tot=unique(num,num+tot)-num;
	memset(arr[0],0,tot+1<<2);
	memset(arr[1],0,tot+1<<2);
	for(int i=0,cnt=0;i<n;++i){
		if(!ope[i].fi){
			int l=lower_bound(num,num+tot,ope[i].se)-num+1,
				r=lower_bound(num,num+tot,++cnt+ope[i].se)-num+1;
			L[cnt]=l;
			R[cnt]=r;
			printf("%d\n",calc(arr[0],l)-calc(arr[1],r+1));
			add(arr[0],l,1);
			add(arr[1],r,1);
		}
		else{
			int l=L[ope[i].se],r=R[ope[i].se];
			add(arr[0],l,-1);
			add(arr[1],r,-1);
		}
	}
}
int main(){
	int kase=0;
	while(~scanf("%d",&n)){
		printf("Case #%d:\n",++kase);
		solve();
	}
	return 0;
}
/*
	
	Jun.27.16
	
	Tags:discretize,BIT
	Submissions:2
	
	Memory(KB) 7364
	Time(ms) 826
	Length(Bytes) 1270
	
*/
