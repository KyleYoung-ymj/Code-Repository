#include<cstdio>
#include<cctype>
const int N=5e4+5;
int n,bit[N]={0};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),!isdigit(c));
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),isdigit(c));
}
void add(int k,int x){
	while(k<=n){
		bit[k]+=x;
		k+=k&-k;
	}
}
int sum(int k){
	int res=0;
	while(k){
		res+=bit[k];
		k&=k-1;
	}
	return res;
}
int main(){
	int cas,kase=0,a,b;
	char str[10];
	rd(cas);
	while(cas--){
		rd(n);
		for(int i=1;i<=n;++i){
			rd(a);
			add(i,a);
		}
		printf("Case %d:\n",++kase);
		while(true){
			scanf("%s",str);
			if(str[0]=='E')break;
			if(str[0]=='Q'){
				rd(a);
				rd(b);
				printf("%d\n",sum(b)-sum(a-1));
			}
			else{
				rd(a);
				rd(b);
				add(a,str[0]=='A'?b:-b);
			}
		}
		for(int i=1;i<=n;++i)
			bit[i]=0;
	}
	return 0;
}
/*
	
	Dec.12.15
	
	Tags:Data Structure,BIT
	Submissions:1
	
	Exe.Time 312MS
	Exe.Memory 1608K
	Code Len. 840B
	
*/
