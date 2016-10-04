#include<cstdio>
const int N=205;
int n,m,sum[N][N];
bool num[N][N];
char str[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
int solve(int L,int R){
	int mx=0;
	for(int i=1,pre=-1;i<=m;++i){
		if(!num[L][i]||!num[R][i]){
			pre=-1;
			continue;
		}
		if(sum[R][i]-sum[L-1][i]==R-L+1){
			if(~pre)Max(mx,i-pre+1);
			else pre=i;
		}
	}
	return mx*(R-L+1);
}
int main(){
	freopen("fortmoo.in","r",stdin);
	freopen("fortmoo.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%s",str+1);
		for(int j=1;j<=m;++j){
			sum[i][j]=sum[i-1][j]+(num[i][j]=str[j]=='.');
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			Max(ans,solve(i,j));
	printf("%d\n",ans);
	return 0;
}
