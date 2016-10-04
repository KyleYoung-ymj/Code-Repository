#include<cstdio>
#include<cctype>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+5;
vector<int>letter[30],tmp;
void Rd(char &a){
    while(a=getchar(),!isalpha(a));
}
int main(){
    int n,m;
    char str[N];
    scanf("%d %d",&n,&m);
    scanf("%s",str);
    for(int i=0;i<n;++i)
        letter[str[i]-'a'].push_back(i);
    while(m--){
        char a,b;
        Rd(a);Rd(b);
        int from=a-'a',to=b-'a';
        letter[from].swap(letter[to]);
    }
    for(int i=0;i<26;++i){
        int sz=letter[i].size();
        for(int j=0;j<sz;++j)
            str[letter[i][j]]=i+'a';
    }
    for(int i=0;i<n;++i)
        printf("%c",str[i]);
    puts("");
    return 0;
}
/*
	
	Oct.25.15
	Submit:1
	
	Time 30ms
	Memory 1900 KB
	
*/
