#include<cstdio>
int num[15];
bool mark[10];
bool solve(int n){
	if(n<4)return false;
	for(int i=0;i<n;++i)
		if(num[i]>9||!num[i])return false;
	for(int i=1;i<10;++i)
		mark[i]=false;
	for(int i=0;i<n-1;++i){
		mark[num[i]]=true;
		if(mark[num[i+1]])return false;
		if(num[i]==1&&num[i+1]==3&&!mark[2])return false;
		if(num[i]==4&&num[i+1]==6&&!mark[5])return false;
		if(num[i]==7&&num[i+1]==9&&!mark[8])return false;
		if(num[i]==1&&num[i+1]==7&&!mark[4])return false;
		if(num[i]==2&&num[i+1]==8&&!mark[5])return false;
		if(num[i]==3&&num[i+1]==9&&!mark[6])return false;
		if(num[i]==3&&num[i+1]==1&&!mark[2])return false;
		if(num[i]==6&&num[i+1]==4&&!mark[5])return false;
		if(num[i]==9&&num[i+1]==7&&!mark[8])return false;
		if(num[i]==7&&num[i+1]==1&&!mark[4])return false;
		if(num[i]==8&&num[i+1]==2&&!mark[5])return false;
		if(num[i]==9&&num[i+1]==3&&!mark[6])return false;
		if(num[i]==1&&num[i+1]==9&&!mark[5])return false;
		if(num[i]==9&&num[i+1]==1&&!mark[5])return false;
		if(num[i]==3&&num[i+1]==7&&!mark[5])return false;
		if(num[i]==7&&num[i+1]==3&&!mark[5])return false; 
	}
	return true;
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i)
			scanf("%d",&num[i]);
		puts(solve(n)?"valid":"invalid");
	}
	return 0;
}
/*
	
	Mar.13.16
	
	Tags:Implementation
	Submissions:5
	
	Exe.Time 171MS
	Exe.Memory 1420K
	Code Len. 1526B
	
*/
