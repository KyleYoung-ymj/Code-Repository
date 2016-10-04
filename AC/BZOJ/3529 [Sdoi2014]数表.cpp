#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5,Q=2e4+5,INF=0x7fffffff;
bool is_prime[N];
int prime[N],sigma[N],mob[N],arr[N],bit[N]={0},ans[Q];
struct Query{
    int n,m,a,id;
    inline void rd(){
        scanf("%d%d%d",&n,&m,&a);
        if(n>m)swap(n,m);
    }
    inline bool operator <(const Query &tmp)const{
        return a<tmp.a;
    }
}query[Q];
inline bool cmp(int a,int b){
    return sigma[a]<sigma[b];
}
void sieve(){
    memset(is_prime,true,N);
    is_prime[0]=is_prime[1]=false;
    mob[1]=1;
    int tot_prime=0;
    for(int i=2;i<N;++i){
        if(is_prime[i]){
            prime[tot_prime++]=i;
            mob[i]=-1;
        }
        for(int j=0,mul;j<tot_prime&&(mul=i*prime[j])<N;++j){
            is_prime[mul]=false;
            if(i%prime[j])mob[mul]=-mob[i];
            else{
                mob[mul]=0;
                break;
            }
        }
    }
    for(int i=1;i<N;++i)
        for(int j=i;j<N;j+=i)
            sigma[j]+=i;
}
void add(int x,int a){
    while(x<N){
        bit[x]+=a;
        x+=x&-x;
    }
}
int sum(int x){
    int res=0;
    while(x){
        res+=bit[x];
        x&=x-1;
    }
    return res;
}
int main(){
    int q;
    scanf("%d",&q);
    sieve();
    for(int i=0;i<q;++i){
        query[i].rd();
        query[i].id=i;
    }
    sort(query,query+q);
    for(int i=1;i<N;++i)
        arr[i]=i;
    sort(arr+1,arr+N,cmp);
    for(int i=0,cur=1;i<q;++i){
        while(cur<N&&sigma[arr[cur]]<=query[i].a){
            for(int j=1;arr[cur]*j<N;++j)
                add(arr[cur]*j,sigma[arr[cur]]*mob[j]);
            ++cur;
        }
        int n=query[i].n,m=query[i].m;
        for(int j=1,last;j<=n;j=last+1){
            last=min(n/(n/j),m/(m/j));
            ans[query[i].id]+=(n/j)*(m/j)*(sum(last)-sum(j-1));
        }
    }
    for(int i=0;i<q;++i)
        printf("%d\n",ans[i]&INF);
    return 0;
}
/*
	
	Apr.21.16
	
	Tags:Mathematics,Number Theory,Mobius Inversion,bit
	Submissions:2
	
	Memory 3252kb
	Time 3640ms
	Code Length 1823B
	
*/
