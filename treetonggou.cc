#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i,m,n) for(int i=m;i<=n;i++)
#define MAXN 1000
//fully use struct or class to realize data packing 
//and module coding
static int A=3,B=7,D=1,E=0XFFFFFF;
struct Tree{
  int Root;
  int N;
  vector<int> Edges[MAXN];
  int Wgt[MAXN];
  Tree(int i,int j){N=i;Root=j;}
  void init(){
    rep(i,1,N) Wgt[i]=0;
    dfs(Root);
  }
  void dfs(int u){
    int (&V)[MAXN]=Wgt;
    int s=A*V[u]+D;
    for(int i=0;i<Edges[u].size();i++){
        int v=Edges[u][i];
        dfs(v);
        int t=V[v];
        s+=B*t;
    }
    V[u]=s%E;
  }
};
struct cmp{
  bool operator()(const pair<int,int>&p1,const pair<int,int>&p2){
    return p1.second<p2.second;
  }
}mycmp;
//compare tree1.u with tree2.v
bool rfs(int u,int v,Tree &tree1,Tree &tree2){
  int (&V1)[MAXN]=tree1.Wgt;
  int (&V2)[MAXN]=tree2.Wgt;
  vector<int> (&Edges1)[MAXN]=tree1.Edges;
  vector<int> (&Edges2)[MAXN]=tree2.Edges;
  if(V1[u]!=V2[v]) return false;//not equal
  if(Edges1[u].size()!=Edges2[v].size()) return false;
  vector<pair<int,int> > vec1,vec2;
  for(int i=0;i<Edges1[u].size();i++){
      int v1=Edges1[u][i];
      vec1.push_back(pair<int,int>(v1,V1[v1]));
      int v2=Edges2[v][i];
      vec2.push_back(pair<int,int>(v2,V2[v2]));
  }
  sort(vec1.begin(),vec1.end(),mycmp);
  sort(vec2.begin(),vec2.end(),mycmp);
  cout<<"(<"<<u<<","<<V1[u]<<">[";
  for(int i=0;i<vec1.size();i++){
    pair<int,int> p1=vec1[i];
    pair<int,int> p2=vec2[i];
    if(p1.second!=p2.second) return false;
    if(!rfs(p1.first,p2.first,tree1,tree2)) return false;
  }
  cout<<"])";
  return true;
}
int main(){
  int N,M;//edge num
  int r1,r2;
  cin>>N; 
  cin>>r1>>r2;
  Tree tree1(N,r1),tree2(N,r2);
  rep(i,1,N-1){
    int a,b;
    cin>>a>>b;
    tree1.Edges[a].push_back(b);
  }
  rep(i,1,N-1){
    int a,b;
    cin>>a>>b;
    tree2.Edges[a].push_back(b);
  }
  tree1.init();tree2.init();
  cout<<rfs(tree1.Root,tree2.Root,tree1,tree2);
  return 0;
}
