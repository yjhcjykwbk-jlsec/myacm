#include "test.h"
#include <queue>
int N;
int dis[MAXN];
int road[MAXN][MAXN];
int dinic_dfs(int u,int c){
  if(u==N) return c;
  int r=0;
  rep(i,0,N){
    if(road[u][i]>0&&dis[i]>dis[u]){
      int c1=min(c,road[u][i]);
      int s=dinic_dfs(i,c1);
      if(s>0){
        road[u][i]-=s;road[i][u]+=s;
        c-=s;r+=s;
        if(c<=0) break;
      } 
    }
  }
  return r;
}
int dinic_bfs(){
  queue<int> vqueue;
  bool tag[MAXN];
  memset(tag,0,sizeof(tag));
  vqueue.push(0);
  dis[0]=0;
  while(!vqueue.empty()) {
    int u=vqueue.front();
    vqueue.pop();
    rep(i,0,N){
      if(road[u][i]&&!tag[i]){ 
        tag[i]=true;
        dis[i]=dis[u]+1;
        vqueue.push(i);
      }
    }
  }
}
int extend_gph(){
  int res=0;
  while(true){
    dinic_bfs();
    int s=dinic_dfs(0,NMAX);
    if(s<=0) break;
    res+=s;
  }
  return res;
}
int main(){
  cin>>N;//T的下标
  rep(i,0,N) rep(j,0,N) road[i][j]=0;
  int M;
  cin>>M;
  rep(i,1,M){
    int a,b,c;
    cin>>a>>b>>c;
    road[a][b]=c;
  }
  rep(i,0,N){cout<<endl; rep(j,0,N) cout<<road[i][j]<<"\t";}
  cout<<extend_gph()<<endl;
  return 0;
}
