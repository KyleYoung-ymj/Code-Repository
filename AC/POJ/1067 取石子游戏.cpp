#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double p=(sqrt(5)-1)/2;// CE:C++
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		if(n>m)swap(n,m);
		printf("%d\n",n==(int)((m-n)/p)?0:1);
	}
	return 0;
}
/*
	
	May.18.16
	
	Tags:Wythoff Game
	Submissions:2
	
	Memory 388K
	Time 0MS
	Code Length 231B
	
*/
