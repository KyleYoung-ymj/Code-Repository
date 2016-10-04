#include<cstdio>
#include<cstring>
typedef unsigned long long ull;
const int N=2e5+5;
const ull B=1e4+7,P0=1e9+7,P1=1e9+9;
int n,m,p,tot=0,num[N],ans[N];
ull pat_sum=0,pat_pro=1,mod0_pat_pro=1,mod1_pat_pro=1,sum[N],pro[N],mod0_pro[N],mod1_pro[N];
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;++i)
		scanf("%d",&num[i]);
	int tmp;
	for(int i=1;i<=m;++i){
		scanf("%d",&tmp);
		pat_sum+=tmp;
		pat_pro*=tmp;
		mod0_pat_pro=1ull*mod0_pat_pro*tmp%P0;
		mod1_pat_pro=1ull*mod1_pat_pro*tmp%P1;
	}
	for(int i=1;i<=p;++i)
		mod0_pro[i]=mod1_pro[i]=pro[i]=sum[i]=num[i];
	for(int i=p+1;i<=n;++i){
		mod0_pro[i]=1ull*mod0_pro[i-p]*num[i]%P0;
		mod1_pro[i]=1ull*mod1_pro[i-p]*num[i]%P1;
		pro[i]=pro[i-p]*num[i];
		sum[i]=sum[i-p]+num[i];
	}
	for(int i=1;i<=p;++i){
		ull en=i+1ull*(m-1)*p;
		if(en>n)break;
		if(sum[en]==pat_sum
		   &&pro[en]==pat_pro
		   &&mod0_pro[en]==mod0_pat_pro
		   &&mod1_pro[en]==mod1_pat_pro)
			ans[tot++]=i;
	}
	for(int i=p+1;i<=n;++i){
		ull en=i+1ull*(m-1)*p;
		if(en>n)break;
		if(sum[i-p]+pat_sum==sum[en]
		   &&pro[i-p]*pat_pro==pro[en]
		   &&1ull*mod0_pro[i-p]*mod0_pat_pro%P0==mod0_pro[en]
		   &&1ull*mod1_pro[i-p]*mod1_pat_pro%P1==mod1_pro[en])
			ans[tot++]=i;
	}
	printf("%d\n",tot);
	for(int i=0;i<tot;++i)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}
/*
	
	Origin:CodeForces 368D
	Tags:Hash
		
	Nov.29.15
	Submit:3
	
	Memory 7636K
	Time 109ms
	Code Length 1301B
	
*/
