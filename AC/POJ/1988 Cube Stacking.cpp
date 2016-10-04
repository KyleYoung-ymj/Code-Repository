#include<cstdio>
const int N=3e4+5;
int par[N],dep[N],sum[N];
int find(int x){
	if(par[x]==x)return x;
	int root=find(par[x]);//must find up first to update 
	dep[x]+=dep[par[x]];
	return par[x]=root;
}
void unite(int a,int b){
	a=find(a);
	b=find(b);
	par[a]=b;
	dep[a]+=sum[b];
	sum[b]+=sum[a];//Excellent!Think it carefully yourself!!
}
int main(){
	int p,x,y;
	char str[5];
	scanf("%d",&p);
	for(int i=0;i<N;++i){
		par[i]=i;
		dep[i]=0;
		sum[i]=1;
	}
	while(p--){
		scanf("%s",str);
		if(str[0]=='M'){
			scanf("%d%d",&x,&y);
			unite(x,y);
		}
		else{
			scanf("%d",&x);
			find(x);
			printf("%d\n",dep[x]);
		}
	}
	return 0;
}
/*
	
	Jan.05.16
	
	Tags:Union Find,classic
	Submissions:2
	
	Memory 516K
	Time 250MS
	Code Length 563B
	
*/
