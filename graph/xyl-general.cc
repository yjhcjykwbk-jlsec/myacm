#include "../test.h"
int N;
int link[MAXN];
bool pre[MAXN];//是否find过
bool flag[MAXN];//是否在访问路径中
vector<int> Edges[MAXN];//
void conn(int i,int j){
  link[i]=j;link[j]=i;
}
bool find(int i){
  for(vector<int>::iterator it=Edges[i].begin();it!=Edges[i].end();it++){
    int j=*it;
    if(link[j]==-1){conn(i,j);return true;}
    else if(!pre[j]&&!flag[j]){
      pre[j]=true;
      flag[j]=true,flag[link[j]]=true;
      if(find(link[j])){//j未匹配，或者边(j,link[j])未经过过
        conn(i,j);return true;}
      flag[j]=false,flag[link[j]]=false;
    }
  }
  return false;
}
int extend(){
  memset(link,-1,sizeof(link));
  int res=0;
  rep(i,1,N){
    if(link[i]==-1){
      memset(flag,0,sizeof(flag));
      memset(pre,0,sizeof(pre));
      find(i)&&++res;
    }
  }
  return res;
}
int main(){
  int M;
  cin>>N>>M;
  rep(i,1,M){
    int a,b;cin>>a>>b;
    Edges[a].push_back(b);
    Edges[b].push_back(a);
  }
  // rep(i,1,N){
    // cout<<i<<endl;
    // rep(j,0,Edges[i].size()-1)
    // cout<<Edges[i][j]<<",";
    // cout<<endl;
  // }
 cout<<extend()<<endl;
 rep(i,1,N)
   if(link[i]>i) 
     cout<<i<<":"<<link[i]<<endl;
  return 0;
}


