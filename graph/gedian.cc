///tarjian算法
#include "../test.h"
bool gph[MAXN][MAXN];
int dfn[MAXN];//记录编号
int low[MAXN];//记录能够共圈的点
int scc[MAXN];
vector<int> gedians;
vector<pair<int,int> > gebians;
vector<int> gens;
stack<int> sstack;
int N;
void init(){
  memset(low,-1,sizeof(low));
  memset(dfs,-1,sizeof(dfs));
  memset(scc,-1,sizeof(scc));
  gedians.clear();
  gebians.clear();
  gens.clear();
  sstack.clear();
  memset(gph,0,sizeof(gph));
}
int cnt=0;
void visit(u){
  low[u]=dfn[u]=cnt++;
  sstack.push(u);
  rep(v,0,N){
    if(gph[u][v]){
      if(dfn[v]==-1){
        visit(v);
        low[u]=min(low[v],low[u]);
        if(low[v]>=dfn[u]) //u->v 如果切断u将断开v分支，u是割点
        {
          if(low[v]>dfn[u]){ gebians.push(pair<int,int> (u,v));}
          gedians.push(u);
        }
      }
      else if(scc[v]==-1) low[u]=min(low[u],dfn[v]);
    }
  }
  //遇到联通根节点，记录连通分支
  int s;
  if(low[u]==dfn[u]) {
    gens.push(u);//u是连通分支根节点
    do{
      s=sstack.top();sstack.pop();
      scc[s]=u;
    }while(s!=u);
  }
}
int main(){
  init();
  int M;
  cin>>N>>M;
  rep(i,1,M){
    int a,b,;
    cin>>a>>b;gph[a][b]=true; 
  }
  rep(i,1,N){
    if(dfn[i]==-1){
     visit(i);
    }
  } 
  rep(i,1,N)
    cout<<"low:"<<low[i]<<" dfn:"<<dfn[i]<<" scc:"<<scc[i]<<endl;
  

