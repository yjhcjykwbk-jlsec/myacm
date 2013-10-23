#include <stdio.h>
#include <string.h>
#define MAXN 400
int S=0,L,R;
bool Map[101][301];
bool Vis[301];
int Link[301];
bool dfs(int s){
  for(int t=1;t<=R;t++){
    if(!Vis[t]&&Map[s][t]){
      Vis[t]=true;//L can only be visited via L=Link[R],so if visit[R]=true,L will not be visited any more
      if(Link[t]==-1||
          dfs(Link[t])) {
        Link[t]=s;
        return true;
      }
    }
  }
  return false;
} 
void init(){
  int a,n;
  scanf("%d %d",&L,&R);
  memset(Map,0,sizeof(Map));
  for(int i=1;i<=R;i++)   Link[i]=-1;
  for(int i=1;i<=L;i++){
    scanf("%d",&n);
    while(n-->0){
      scanf("%d",&a);
      Map[i][a]=true;
    }
  }
}
int main(){
  int cases;scanf("%d",&cases);
  while(cases-->0){
    init();
    int i;for(i=1;i<=L;i++){
      memset(Vis,0,sizeof(Vis));
      if(!dfs(i)) break;
    }
    if(i==L+1) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}
