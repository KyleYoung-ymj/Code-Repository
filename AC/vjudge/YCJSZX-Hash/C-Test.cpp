#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const ull B=1e9+7;
const int N=1e5+5,INF=3e5+5;
char str[4][N<<1];
int sum,len[4];
inline void Min(int &a,int b){
	if(b<a)a=b;
}
bool contain(int a,int b){
	if(len[a]<len[b])return false;
	ull hash=0,pat=0,pow=1;
	for(int i=0;i<len[b];++i){
		hash=hash*B+str[a][i];
		pat=pat*B+str[b][i];
		pow*=B;
	}
	for(int i=0;i+len[b]<=len[a];++i){
		if(hash==pat)return true;
		if(i+len[b]<len[a])hash=hash*B+str[a][i+len[b]]-str[a][i]*pow;
	}
	return false;
}
int find(int a,int b){
	int mx=0,en=min(len[a],len[b]);
	ull pow=1,hash0=0,hash1=0;
	for(int i=0;i<en;++i){
		hash0=hash0*B+str[a][i];
		hash1+=str[b][len[b]-i-1]*pow;
		pow*=B;
		if(hash0==hash1)mx=i+1;
	}
	return mx;
}
inline int find_mx(int a,int b){
	return max(find(a,b),find(b,a));
}
inline int solve(int a,int b,int c){
	len[3]=0;
	for(int i=0;i<len[a];++i)
		str[3][len[3]++]=str[a][i];
	int len_tmp=find(b,a);
	for(int i=len_tmp;i<len[b];++i)
		str[3][len[3]++]=str[b][i];
	return sum-len_tmp-find(c,3);
}
int main(){
	for(int i=0;i<3;++i){
		scanf("%s",str[i]);
		len[i]=strlen(str[i]);
	}
	sum=len[0]+len[1]+len[2];
	for(int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			if(i!=j&&contain(i,j))
				for(int k=0;k<3;++k)
					if(k!=i&&k!=j){
						printf("%d\n",len[i]+len[k]-find_mx(i,k));
						return 0;
					}
	int ans=INF;
	Min(ans,solve(0,1,2));
	Min(ans,solve(0,2,1));
	Min(ans,solve(1,0,2));
	Min(ans,solve(1,2,0));
	Min(ans,solve(2,0,1));
	Min(ans,solve(2,1,0));
	printf("%d\n",ans);
	return 0;
}
/*
	
	Nov.28.15
	Submit:5
	
	Memory 792KB
	Time 62ms
	Code Length 1585B
	
*/
