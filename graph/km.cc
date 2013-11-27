#define EDGE pair<int,int>
int p[MAXN],q[MAXN];
bool find(int u){//为左L[]寻找匹配
  //if(p[u]==0) return true;
  tag[u]=true;//u is in the L[] now
  for(EDGE e in edges[u]){
    int v=e.first,w=e.second;
    if(!visit[v]) {
      visit[v]=true;
      tag[v]=u;//v is in the R[] now
      if(!pre[v]||find(pre[v])){
        pre[v]=u;
        return true;
      }
    }
  }
}
void calc(){
  rep(i,1,N){
    while(!find(i)){
      shoushu();
    }
  }
}
void shoushu(){

