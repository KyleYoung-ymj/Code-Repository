#include<iostream>
using namespace std;
const int P=1000000007;
int main(){
	int a,b,ans=1;
	cin>>a>>b;
	while(b){
		if(b&1)ans=1LL*ans*a%P;
		a=1LL*a*a%P;
		b>>=1;
	}
	cout<<ans<<endl;
} 
