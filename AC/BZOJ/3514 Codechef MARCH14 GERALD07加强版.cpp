#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+5,NODE=N<<1,INF=0x7fffffff;
int n,m,pre[N],id[NODE];
struct Edge{
    int u,v;
}edge[N];
struct LCT{
    int par[NODE],ch[NODE][2],mi[NODE],stk[NODE];
    bool flip[NODE];
    void init(){
        memset(par,0,sizeof(par));
        memset(ch,0,sizeof(ch));
        memset(flip,false,sizeof(flip));
        for(int i=1;i<=n+m;++i)
            mi[i]=i;
    }
    void push_up(int k){
        mi[k]=k;
        for(int i=0;i<2;++i)
            if(ch[k][i]&&id[mi[ch[k][i]]]<id[mi[k]])mi[k]=mi[ch[k][i]];
    }
    void push_down(int k){
        if(!flip[k])return;
        swap(ch[k][0],ch[k][1]);
        flip[ch[k][0]]^=1;
        flip[ch[k][1]]^=1;
        flip[k]=false;
    }
    inline bool is_root(int x){
        return ch[par[x]][0]!=x&&ch[par[x]][1]!=x;
    }
    void rotate(int x,bool f){
        int y=par[x];
        par[ch[x][f]]=y;
        ch[y][!f]=ch[x][f];
        par[x]=par[y];
        if(!is_root(y))ch[par[y]][ch[par[y]][1]==y]=x;
        par[y]=x;
        ch[x][f]=y;
        push_up(y);
        push_up(x);
    }
    void update(int x){
        int top=0;
        stk[top++]=x;
        for(;!is_root(x);x=par[x])
            stk[top++]=par[x];
        while(top)push_down(stk[--top]);
    }
    void Splay(int x){
        update(x);
        while(!is_root(x)){
            int y=par[x];
            if(is_root(y))rotate(x,ch[y][0]==x);
            else{
                bool flag=ch[par[y]][0]==y;
                if(ch[y][flag]==x)rotate(x,!flag);
                else rotate(y,flag);
                rotate(x,flag);
            }
        }
    }
    void Access(int x){
        for(int y=0;x;y=x,x=par[x]){
            Splay(x);
            ch[x][1]=y;
            push_up(x);
        }
    }
    void make_root(int x){
        Access(x);
        Splay(x);
        flip[x]^=1;
    }
    int find_root(int x){
        Access(x);
        Splay(x);
        for(;;x=ch[x][0]){
            if(!ch[x][0]){
                Splay(x);
                return x;
            }
        }
    }
    void link(int u,int v){
        make_root(u);
        par[u]=v;
        Access(u);
    }
    void cut(int u,int v){
        make_root(u);
        Access(v);
        Splay(v);
        ch[v][0]=par[u]=0;
        push_up(v);
    }
    int query_mi(int u,int v){
        make_root(u);
        Access(v);
        Splay(v);
        return mi[v];
    }
}lct;
struct Chairman_Tree{
    static const int LG=20,M=(N<<2)+N*LG;// RE:M=N*LG
    int allc,Tid[N],Lson[M],Rson[M],sum[M];
    inline void init(){
        allc=0;
    }
    void construct(int L,int R,int &tid){
        sum[tid=++allc]=0;
        if(L==R)return;
        int mid=L+R>>1;
        construct(L,mid,Lson[tid]);
        construct(mid+1,R,Rson[tid]);
    }
    void update(int oid,int L,int R,int x,int &tid){
        tid=++allc;
        Lson[tid]=Lson[oid];
        Rson[tid]=Rson[oid];
        sum[tid]=sum[oid]+1;
        if(L==R)return;
        int mid=L+R>>1;
        if(x<=mid)update(Lson[oid],L,mid,x,Lson[tid]);
        else update(Rson[oid],mid+1,R,x,Rson[tid]);
    }
    int query(int Lt,int Rt,int L,int R,int k){
        if(L>=k)return 0;
        if(R<k)return sum[Rt]-sum[Lt];
        int mid=L+R>>1;
        return query(Lson[Lt],Lson[Rt],L,mid,k)+query(Rson[Lt],Rson[Rt],mid+1,R,k);
    }
    inline int solve(int L,int R){
        return n-query(Tid[L-1],Tid[R],0,m,L);
    }
}T;
void rd(int &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>47);
}
int main(){
    int q,type,L,R,last_ans=0;
    rd(n);rd(m);rd(q);rd(type);
    for(int i=1;i<=n;++i)
        id[i]=INF;
    lct.init();
    T.init();
    T.construct(0,m,T.Tid[0]);
    for(int i=1,u,v;i<=m;++i){
        id[i+n]=i;
        rd(u);rd(v);
        edge[i].u=u;
        edge[i].v=v;
        if(u==v)pre[i]=i;
        else{
            if(lct.find_root(u)!=lct.find_root(v))pre[i]=0;
            else{
                int tmp=lct.query_mi(u,v)-n;
                pre[i]=tmp;
                lct.cut(edge[tmp].u,n+tmp);
                lct.cut(edge[tmp].v,n+tmp);
            }
            lct.link(u,i+n);
            lct.link(v,i+n);
        }
        T.update(T.Tid[i-1],0,m,pre[i],T.Tid[i]);
    }
    while(q--){
        rd(L);rd(R);
        if(type){
	        L^=last_ans;
	        R^=last_ans;
		}
        last_ans=T.solve(L,R);
        printf("%d\n",last_ans);
    }
    return 0;
}

/*
	
	May.04.16
	
	Tags:Graph Theory,LCT,Chairman Tree
	Submissions:9
	
	Memory 69980kb
	Time 42872ms
	Code Length 5038B
	
*/
