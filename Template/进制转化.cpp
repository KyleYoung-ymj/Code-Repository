#include<iostream>
using namespace std;
int main(){
	int n,b,cnt=0,K[15];
	while(n){
		K[cnt++]=n%b;
		n/=b;
	}
	for(int i=cnt-1;i>=0;i--)
		cout<<K[i];
	cout<<endl;
	return 0;
}
