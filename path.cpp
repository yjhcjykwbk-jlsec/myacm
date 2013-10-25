//试图求一条极大路径
//从u出发
//next[]记录了这条路径每个点下一个点
#include <iostream>
#include <set>
using namespace std;
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define N 100
bool vis[N];
int next[N];
set<int> Edges[N];
//从u向后扩展
void extend(int u){
  while(true){
    vis[u]=true;
    int s=u;
    next[u]=-1;
    for(set<int>::iterator it=Edges[u].begin();
        it!=Edges[u].end();it++){
      int v=*it;
      if(!vis[v]){ 
        next[u]=v;
        u=v;
        break;
      }
    }
    if(s==u) break;
  }
}
//从u向前扩展 
int rextend(int u){
  while(true){
    vis[u]=true;
    int s=u;
    for(set<int>::iterator it=Edges[u].begin();
        it!=Edges[u].end();it++){
      int v=*it;
      if(!vis[v]){ 
        next[v]=u;
        u=v;
        break;
      }
    }
    if(s==u) break;
  }
  return u;
} 
//u!=t
//寻找(u,t）之间的路径
bool dfs(int u,int t){
  if(u==t) return true;
  for(set<int>::iterator it=Edges[u].begin();
      it!=Edges[u].end();it++){
    int v=*it;
    if(v==t||(!vis[v]&&dfs(v,t))){ 
      vis[v]=true;
      next[u]=v;
      return true;
    }
  }
  return false;
} 
int getPath(int u){
  extend(u);
  int t=u=rextend(u);
  int v=u;
  while(true){
    u=v;
    v=next[u];
    if(v==-1) break;
    while(true){
      v=next[u];
      dfs(u,v);
      if(v==next[u]) break; 
    }
  }
  return t;
}
int main(){
  rep(i,1,N) next[i]=-1,vis[i]=false;
  int m;
  cin>>m;
  for(int i=1;i<=m;i++){
    int a,b;
    cin>>a>>b;
    cout<<a<<" "<<b<<endl;
    Edges[a].insert(b);
    Edges[b].insert(a);
  }
  int u=getPath(1);
  while(u!=-1){
    cout<<u<<" ";
    u=next[u]; 
  }
  return 0;
}
