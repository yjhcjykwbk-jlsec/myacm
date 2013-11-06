///dfs算法
#include "../test.h"
bool gph[MAXN][MAXN];
int dfn[MAXN];//记录编号
int low[MAXN];//记录能够共圈的点
int scc[MAXN];
vector<int> gedians;
vector<pair<int,int> > gebians;
vector<int> gens;
stack<int> sstack;
#define min(a,b) a<b?a:b
int N;
int cnt;
void init(){
  cnt=1;
  memset(low,-1,sizeof(low));
  memset(dfn,-1,sizeof(dfn));
  memset(scc,-1,sizeof(scc));
}

//dfs scc
void dfs_scc(int u){//p is the parent of u on the 'tree'
  low[u]=dfn[u]=cnt++;
  sstack.push(u);
  rep(v,1,N){
    if(gph[u][v]){
      if(dfn[v]==-1){
        dfs_scc(v);
        low[u]=min(low[v],low[u]);
      }
      else if(scc[v]==-1){
        low[u]=min(low[u],dfn[v]);//v is waiting for u or u's ancestor
      }
    }
  }
  //遇到联通根节点，记录连通分支
  int s;
  if(low[u]==dfn[u]) {
    gens.push_back(u);//u is the root of a connecting branch
    do{
      s=sstack.top();sstack.pop();
      scc[s]=u;
    }while(s!=u);
  }
}

void dfs_gedian(int u,int p){//p is the parent of u on the 'tree'
  low[u]=dfn[u]=cnt++;
  bool isGeDian=false;
  rep(v,1,N){
    if(gph[u][v]&&v!=p){
      if(dfn[v]==-1){
        dfs_gedian(v,u);
        low[u]=min(low[v],low[u]);
        if(low[v]>=dfn[u]) //u->v 如果切断u将断开v分支，u是割点
        {
          if(low[v]>dfn[u]){ gebians.push_back(pair<int,int> (u,v));}
          //u,v is gebian as v tree's low > u
          //which means v tree not connect to any ancestor of u,(<)
          //and not twice connect to u itself(=)
          isGeDian=true;//u is gedian as has a son-tree who's low >= u
        }
      }
      else low[u]=min(low[u],dfn[v]);//make sure low[u]<=dfn[v]
    }
  }
  if(isGeDian) gedians.push_back(u);//u is gedian
}
int main(){
  int M;
  cout<<"test tarjan scc"<<endl;
  cin>>N>>M;
  memset(gph,0,sizeof(gph));
  init();
  rep(i,1,M){
    int a,b;
    cin>>a>>b;gph[a][b]=true; 
  }
  rep(i,1,N){
    if(dfn[i]==-1){
     dfs_scc(i);
    }
  } 
  rep(i,1,N)
    cout<<"low:"<<low[i]<<" dfn:"<<dfn[i]<<" scc:"<<scc[i]<<endl;
  
  cout<<"test tarjan gedian"<<endl;
  rep(i,1,N)
    rep(j,1,N)
      if(gph[i][j]) gph[j][i]=true;
  init();
  rep(i,1,N){
    if(dfn[i]==-1){
     dfs_gedian(i,0);
    }
  } 
  rep(i,1,N)
    cout<<"low:"<<low[i]<<" dfn:"<<dfn[i]<<endl;
  cout<<"gedian:"<<endl;
  rep(i,0,gedians.size()-1)
    cout<<gedians[i]<<" ";cout<<endl;
  cout<<"gebians:"<<endl;
  rep(i,0,gebians.size()-1)
    cout<<gebians[i].first<<","<<gebians[i].second<<" ";cout<<endl;
  return 0;
}
