#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=4e4+5;
const ull B=4e4+7;
int n,m,pos_ans,pos[N];
ull Hash[N],pow_B[N];
char str[N];
inline void Max(int &a,int b){
	if(b>a)a=b;
}
bool cmp(const int &a,const int &b){
	if(Hash[a]!=Hash[b])return Hash[a]<Hash[b];
	return a<b;
}
bool judge(int x){
	int cnt=0;
	ull val=0;
	for(int i=0;i<x;++i)
		val=val*B+str[i];
	for(int i=0;i+x<=n;++i){
		pos[i]=i;
		Hash[i]=val;
		if(i+x<n)val=val*B+str[i+x]-str[i]*pow_B[x];
	}
	pos_ans=-1;
	sort(pos,pos+n-x+1,cmp);
	for(int i=0;i<n-x+1;++i){
		if(i&&Hash[pos[i]]!=Hash[pos[i-1]])cnt=0;
		if(++cnt>=m)Max(pos_ans,pos[i]);
	}
	return ~pos_ans;
}
int main(){
	pow_B[0]=1;
	for(int i=1;i<N;++i)
		pow_B[i]=pow_B[i-1]*B;
	while(scanf("%d",&m)&&m){
		scanf("%s",str);
		n=strlen(str);
		if(!judge(1)){
			puts("none");
			continue;
		}
		int L=1,R=n,ans;
		while(L<=R){
			int mid=L+R>>1;
			if(judge(mid)){
				ans=mid;
				L=mid+1;
			}
			else R=mid-1;
		}
		judge(ans);
		printf("%d %d\n",ans,pos_ans);
	}
	return 0;
}
/*
	
	Nov.28.15
	Submit:7
	
	Time 1529ms
	Code Length 1095B
	
*/
