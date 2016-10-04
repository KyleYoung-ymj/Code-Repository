#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
using namespace std;
const int N=4005,LEN=1005;
typedef long long ll;
char str[N][LEN];
int allc,pre[N*LEN][62]={0},pass[N*LEN]={0},en[N*LEN]={0};
int mp(char c){
	if(isdigit(c))return c^48;
	return islower(c)?c-'a'+36:c-'A'+10;
}
int main(){
	int n,cnt=0;
	while(++cnt&&scanf("%d",&n)&&n){
		allc=0;
		ll ans=0;
		for(int k=0;k<n;++k){
			scanf("%s",str[k]);
			int len=strlen(str[k]),cur=0;
			for(int i=0;i<len;++i){
				int tmp=mp(str[k][i]);
				if(!pre[cur][tmp])
					pre[cur][tmp]=++allc;
				cur=pre[cur][tmp];
				++pass[cur];
			}
			ans+=en[cur]++;
		}
		for(int i=1;i<=allc;++i){
			if(pass[i]>1)ans+=1LL*pass[i]*(pass[i]-1);
			pass[i]=0;
			en[i]=0;
		}
		ans+=n*(n-1)>>1;
		printf("Case %d: ",cnt);
		cout<<ans<<endl;
		for(int i=0;i<=allc;++i)
			for(int j=0;j<62;++j)
				pre[i][j]=0;
	}
	return 0;
}
/*
	
	Nov.21.15
	Submit:8
	
	Time 745ms
	Code Length 889B
	
	When strcmp() two equal strings,
		for example, "that" & "that",
		10 comparisons are required.
	
*/
