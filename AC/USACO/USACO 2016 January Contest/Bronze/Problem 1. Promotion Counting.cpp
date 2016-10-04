#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	int a,b,c,d,e,f,g,h;
	cin>>a>>b>>c>>d>>e>>f>>g>>h;
	cout
	<<d+f+h-c-e-g<<endl
	<<f+h-e-g<<endl
	<<h-g<<endl;
	return 0;
}
