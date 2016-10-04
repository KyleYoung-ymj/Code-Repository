#include<cstdio>
const int N=8e3+5;
typedef long long ll;
int n,num[N];
ll cnt[N<<1]={0};
void rd(int &res){
	res=0;
	char c;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
		while(c=getchar(),c>47);
}
void solve(){
	for(int i=0;i<n;++i)
		rd(num[i]);
	for(int i=0;i<n;++i){
		long long ans=0;
		for(int j=i,ptr=N;j<n;++j){
			if(num[j]>num[i])++ptr;
			else if(num[j]!=num[i])--ptr;
			++cnt[ptr];
		}
		for(int j=i,ptr=N;~j;--j){
			if(num[j]<num[i])++ptr;
			else if(num[j]!=num[i])--ptr;
			ans+=cnt[ptr];
		}
		for(int j=i,ptr=N;j<n;++j){
			if(num[j]>num[i])++ptr;
			else if(num[j]!=num[i])--ptr;
			--cnt[ptr];
		}
		printf("%I64d%c",ans,i==n-1?'\n':' ');
	}
}
int main(){
	while(~scanf("%d",&n))solve();
	return 0;
}
/*
	
	May.26.16
	
	Tags:Brute force
	Submissions:1
	
	Exe.Time 1918MS
	Exe.Memory 1572K
	Code Len. 944B
	
*/
