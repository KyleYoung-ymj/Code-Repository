#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
const int N=3e4+5,M=1e5+5,Q=4e4+5;
int n,tot_edge,allc,head[N],par[N],dep[N],sz[N],son[N],top[N],tid[N];
bool vis[N];
typedef pair<int,int> P;
map<P,bool>del;
struct Edge{
    int to,nxt;
}edge[M<<1];
inline void rd(int &res){
    res=0;
    char c;
    while(c=getchar(),c<48);
    do res=(res<<3)+(res<<1)+(c^48);
        while(c=getchar(),c>=48);
}
struct Operation{
    int type,u,v,ans;
    inline bool Rd(){
        scanf("%d",&type);
        if(type==-1)return false;
        rd(u);rd(v);
        return true;
    }
}ope[Q];
struct Segment_Tree{
    struct Node{
        int L,R,sum;
        bool same;
    }tree[N<<2];
    inline void push_up(int k){
        tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
    }
    inline void push_down(int k){
        if(!tree[k].same)return;
        tree[k<<1].same=tree[k<<1|1].same=true;
        tree[k<<1].sum=tree[k<<1|1].sum=0;
        tree[k].same=false;
    }
    void construct(int L,int R,int k=1){
        tree[k].L=L;
        tree[k].R=R;
        tree[k].sum=R-L+1;
        tree[k].same=false;
        if(L==R)return;
        int mid=L+R>>1;
        construct(L,mid,k<<1);
        construct(mid+1,R,k<<1|1);
    }
    void update(int L,int R,int k=1){
        if(!tree[k].sum)return;
        if(tree[k].L==L&&tree[k].R==R){
            tree[k].sum=0;
            tree[k].same=true;
            return;
        }
        int mid=tree[k].L+tree[k].R>>1;
        if(R<=mid)update(L,R,k<<1);
        else if(L>mid)update(L,R,k<<1|1);
        else{
            update(L,mid,k<<1);
            update(mid+1,R,k<<1|1);
        }
        push_up(k);
    }
    int query(int L,int R,int k=1){
        if(tree[k].L==L&&tree[k].R==R)return tree[k].sum;
        push_down(k);
        int mid=tree[k].L+tree[k].R>>1;
        if(R<=mid)return query(L,R,k<<1);
        if(L>mid)return query(L,R,k<<1|1);
        return query(L,mid,k<<1)+query(mid+1,R,k<<1|1);
    }
}T;
inline void add_edge(int from,int to){
    edge[tot_edge]=(Edge){to,head[from]};
    head[from]=tot_edge++;
}
void Update(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        T.update(tid[top[u]],tid[u]);
        u=par[top[u]];
    }
    if(u==v)return;
    if(dep[u]>dep[v])swap(u,v);
    T.update(tid[son[u]],tid[v]);
}
int Query(int u,int v){
    int res=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        res+=T.query(tid[top[u]],tid[u]);
        u=par[top[u]];
    }
    if(u==v)return res;
    if(dep[u]>dep[v])swap(u,v);
    return res+T.query(tid[son[u]],tid[v]);
}
void pre_dfs(int cur){
    vis[cur]=true;
    sz[cur]=1;
    son[cur]=-1;
    for(int i=head[cur];~i;i=edge[i].nxt){
        int to=edge[i].to;
        if(vis[to]||del.find(P(cur,to))!=del.end())continue;
        par[to]=cur;
        dep[to]=dep[cur]+1;
        pre_dfs(to);
        sz[cur]+=sz[to];
        if(son[cur]==-1||sz[to]>sz[son[cur]])son[cur]=to;
    }
}
void allc_dfs(int cur,int anc){
    vis[cur]=true;
    top[cur]=anc;
    tid[cur]=++allc;
    if(~son[cur])allc_dfs(son[cur],anc);
    else return;
    for(int i=head[cur];~i;i=edge[i].nxt){
        int to=edge[i].to;
        if(vis[to]||to==son[cur]||del.find(P(cur,to))!=del.end())continue;
        allc_dfs(to,to);
    }
}
void dfs(int cur){
    vis[cur]=true;
    for(int i=head[cur];~i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==par[cur]||del.find(P(cur,to))!=del.end())continue;
        if(vis[to])Update(cur,to);
        else dfs(to);
    }
}
void init(){
    memset(vis,false,n+1);
    dep[1]=0;
    pre_dfs(1);
    allc=0;
    T.construct(1,n);
    memset(vis,false,n+1);
    allc_dfs(1,1);
    memset(vis,false,n+1);
    dfs(1);
}
int main(){
    int m,q,u,v;
    rd(n);rd(m);
    tot_edge=0;
    memset(head,-1,n+1<<2);
    while(m--){
        rd(u);rd(v);
        add_edge(u,v);
        add_edge(v,u);
    }
    del.clear();
    for(q=0;ope[q].Rd();++q)
        if(!ope[q].type)del[P(ope[q].u,ope[q].v)]=del[P(ope[q].v,ope[q].u)]=true;
    init();
    for(int i=q-1;~i;--i){
        if(ope[i].type)ope[i].ans=Query(ope[i].u,ope[i].v);
        else Update(ope[i].u,ope[i].v);
    }
    for(int i=0;i<q;++i)
        if(ope[i].type)printf("%d\n",ope[i].ans);
    return 0;
}
/*
	
	Apr.30.16
	
	Tags:Graph Theory,HLD
	Submissions:2
	
	Memory 6920kb
	Time 552ms
	Code Length 4671B
	
*/
