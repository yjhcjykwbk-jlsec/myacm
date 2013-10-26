//试图求一条极大路径
//从u出发
//next[]记录了这条路径每个点下一个点
#include <assert.h>
#include <iostream>
#include <set>
using namespace std;
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define N 100
bool vis[N];
int next[N];//初始为-1
set<int> Edges[N];
//从u向某个方向扩展
//@return 扩展到的最后一个点
int extend(int u,bool direction){
  while(true){
    vis[u]=true;
    int tmp=u;
    for(set<int>::iterator it=Edges[u].begin(); it!=Edges[u].end();it++){
      int v=*it;
      if(!vis[v]){ 
        if(direction) next[u]=v;
        else next[v]=u;
        u=v;
        break;
      }
    }
    if(tmp==u) break;
  }
  return u;
}
//寻找(s,t）之间的路径,不包含st
//u为当前访问的点
//@param s,t都是已标记的
bool dfs(int s,int u,int t){
  //bake vis[u]
  bool tmp=vis[u];
  vis[u]=true;
  for(set<int>::iterator it=Edges[u].begin();
      it!=Edges[u].end();it++){
    int v=*it;
    if((s!=u&&v==t)||!vis[v]&&dfs(s,v,t)){ 
      next[u]=v;
      return true;
    }
  }
  //recover vis[u]
  vis[u]=tmp;
  return false;
} 
int extendPath(int u){
  int t=u,v=u;
  while(true){
    u=v;
    if(next[u]==-1) break;
    while(true){
      v=next[u];
      assert(v!=-1);
      if(!dfs(u,u,v)) break;
    }
  }
  return t;
}
int main(){
  rep(i,1,N) next[i]=-1,vis[i]=false;
  int m; cin>>m;
  for(int i=1;i<=m;i++){
    int a,b;
    cin>>a>>b;
    cout<<a<<" "<<b<<endl;
    Edges[a].insert(b);
    Edges[b].insert(a);
  }

  int u=1;
  extend(u,true);
  int tmp=u=extend(u,false);
  while(u!=-1){
    cout<<u<<" ";
    u=next[u]; 
  }
  cout<<endl<<"after extended"<<endl;
  u=tmp;
  extendPath(u);
  while(u!=-1){
    cout<<u<<" ";
    u=next[u]; 
  }
  return 0;
}
