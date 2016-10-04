#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,num[N],pos[N];
typedef __int64 ll;
ll ans[N];
inline bool cmp(int a,int b){
	return num[a]<num[b];
}
inline ll sqr(int x){
	return 1ll*x*x;
}
inline void Max(ll &a,ll b){
	if(b>a)a=b;
}
void divide(int L,int R){
	if(L>=R)return;
	int pos_mx=L;
	for(int i=L;i<=R;++i){
		pos[i]=i;
		if(num[i]>num[pos_mx]){
			pos_mx=i;
		}
	}
	sort(pos+L,pos+R+1,cmp);
	for(int i=L,ptr_L=L,ptr_R=R,len=R-L+1;i<=R;++i){
		if(pos[i]<pos_mx){
			while(ptr_L<=pos[i]){
				Max(ans[len],1ll*num[pos_mx]*num[pos[i]]);
				++ptr_L;
				--len;
			}
		}
		else if(pos[i]>pos_mx){
			while(ptr_R>=pos[i]){
				Max(ans[len],1ll*num[pos_mx]*num[pos[i]]);
				--ptr_R;
				--len;
			}
		}
		else Max(ans[len],sqr(num[pos_mx]));
	}
	divide(L,pos_mx-1);
	divide(pos_mx+1,R);
}
void solve(){
	for(int i=0;i<n;++i){
		scanf("%d",&num[i]);
		ans[i+1]=0;
	}
	divide(0,n-1);
	for(int i=1;i<=n;++i)
		printf("%I64d\n",ans[i]);
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	May.22.16
	
	Tags:...
	Submissions:2
	
	Exe.Time 2074MS
	Exe.Memory 2976K
	Code Len. 1088B
	
*/
