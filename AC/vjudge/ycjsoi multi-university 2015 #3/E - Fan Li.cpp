#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e5+5,LG_N=18,S=2333335,LG_S=23,mod=998244353;
int n,dp[N],lg[N],ST[N][LG_N],bit_mx[N],bit_sum[2][N];
struct UNIT{
	int R,l,r,val;
	inline bool operator <(const UNIT &tmp)const{
		if(val!=tmp.val)return val<tmp.val;
		return R<tmp.R;
	}
}arr[N*LG_S];
void init(){
	memset(dp,0,sizeof dp);
	memset(bit_mx,0,sizeof bit_mx);
	memset(bit_sum,0,sizeof bit_sum);
	for(int i=2,j=1;i<N;++i){
		lg[i]=j;
		if(!(i&(i-1)))++j;
	}
}
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int query_gcd(int L,int R){
	int k=lg[R-L+2]-1;
	return gcd(ST[L][k],ST[R-(1<<k)+1][k]);
}
inline void Max(int &a,int b){
	if(b>a)a=b;
}
inline void Min(int &a,int b){
	if(b<a)a=b;
}
int query_mx(int x){
	int res=0;
	while(x){
		Max(res,bit_mx[x]);
		x&=x-1;
	}
	return res;
}
void update_mx(int x,int val){
	while(x<=n){
		Max(bit_mx[x],val);
		x+=lowbit(x);
	}
}
inline void mod_add(int &a,int b){
	if((a+=b)>=mod)a-=mod;
}
int query_sum(bool type,int x){
	int res=0;
	while(x){
		mod_add(res,bit_sum[type][x]);
		x&=x-1;
	}
	return res;
}
int query_itv_sum(bool type,int L,int R){
	int res=query_sum(type,R)-query_sum(type,L-1);
	if(res<0)res+=mod;
	return res;
}
void update_sum(bool type,int x,int val){
	while(x<=n){
		mod_add(bit_sum[type][x],val);
		x+=lowbit(x);
	}
}
void solve(){
	for(int i=1;i<=n;++i)
		rd(ST[i][0]);
	for(int j=1;1<<j<=n;++j)
		for(int i=1;i+(1<<j)-1<=n;++i)
			ST[i][j]=gcd(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
	int tot=0;
	for(int R=1;R<=n;++R){
		int r=R;
		while(r){
			int val=query_gcd(r,R),
				bin_L=1,bin_R=r,l;
			while(bin_L<=bin_R){
				int mid=bin_L+bin_R>>1;
				if(query_gcd(mid,R)==val){
					l=mid;
					bin_R=mid-1;
				}
				else bin_L=mid+1;
			}
			arr[tot++]=(UNIT){R,l,r,val};
			r=l-1;
		}
	}
	sort(arr,arr+tot);
	int ans=0,ans_sum;
	for(int i=0,j;i<tot;){
		for(j=i;j==i||j<tot&&arr[j].val==arr[j-1].val;++j){
			int R=arr[j].R,l=arr[j].l,r=arr[j].r,sum=0,
				pre_L,pre_R,bin_L,bin_R;
			dp[R]=query_mx(r-1)+1;
			if(dp[R]>1){
				bin_L=i;
				bin_R=j-1;
				while(bin_L<=bin_R){
					int mid=bin_L+bin_R>>1;
					if(dp[arr[mid].R]+1==dp[R]){
						pre_L=mid;
						bin_R=mid-1;
					}
					else if(dp[arr[mid].R]+1>dp[R])bin_R=mid-1;
					else bin_L=mid+1;
				}
				bin_L=pre_L;
				bin_R=j-1;
				while(bin_L<=bin_R){
					int mid=bin_L+bin_R>>1;
					if(dp[arr[mid].R]+1==dp[R]){
						pre_R=mid;
						bin_L=mid+1;
					}
					else bin_R=mid-1;
				}
				pre_L=arr[pre_L].R;
				pre_R=arr[pre_R].R;
				if(pre_L<l){
					sum=1ll*query_itv_sum(0,pre_L,min(l-1,pre_R))*(r-l+1)%mod;
				}
				Max(pre_L,l);
				Min(pre_R,r-1);
				if(pre_L<=pre_R){
					sum=(sum+1ll*query_itv_sum(0,pre_L,pre_R)*r-query_itv_sum(1,pre_L,pre_R))%mod;
					if(sum<0)sum+=mod;
				}
			}
			else sum=r-l+1;
			if(dp[R]>ans){
				ans=dp[R];
				ans_sum=sum;
			}
			else if(dp[R]==ans){
				mod_add(ans_sum,sum);
			}
			update_mx(R,dp[R]);
			update_sum(0,R,sum);
			update_sum(1,R,1ll*sum*R%mod);
		}
		for(;i<j;++i){
			int x=arr[i].R;
			dp[x]=0;
			while(x<=n){
				bit_mx[x]=bit_sum[0][x]=bit_sum[1][x]=0;
				x+=lowbit(x);
			}
		}
	}
	printf("%d %d\n",ans,ans_sum);
}
int main(){
	init();
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	Jun.22.16
	
	Tags:dp,bit
	Submissions:2
	
	Memory(KB) 44856
	Time(ms) 2152
	Length(Bytes) 3381
	
*/
