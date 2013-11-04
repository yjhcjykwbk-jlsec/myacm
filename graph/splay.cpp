//http://wenku.baidu.com/view/7f0ff024ccbff121dd3683ac.html
//伸展树的应用:营业额统计
//author: stevenberge
//time:   2013/10/22 12:00
#include <stdio.h>
#include <assert.h>
struct Node{
  int size;
  int info;
  Node* child[2];
  Node* pre;
  Node(int a):info(a){
    pre=NULL;
    size=1;//self
    child[0]=child[1]=NULL;
  }
};
void print(Node *node){
  if(!node) printf("(NULL)\n");
  else
  printf("(info:%d,size:%d,l:%x,r:%x,pre:%x)\n",node->info,node->size,node->child[0],node->child[1],node->pre);
} 
struct SplayTree{
  Node *root;
  SplayTree(){
    root=NULL;
  }
  void rotate(Node* x,bool c){
    //zig or zag 
    Node* y=x->pre,* z=y->pre;
    //c=y->child[0]==x;
    assert(y->child[!c]==x);
    y->child[!c]=x->child[c];
    if(x->child[c]) x->child[c]->pre=y;
    x->child[c]=y,y->pre=x;
    //y's parent now is x's parent
    if(z) z->child[z->child[1]==y]=x;
    x->pre=z;
    if(root==y) root=x;//root 变成x
  }
  //when f==NULL, x will be rotated to the root
  void splay(Node* x,Node *f){
    while(x->pre!=f){
      Node *y=x->pre,*z=x->pre->pre;
      //zig or zag
      if(z==f){
        rotate(x,!(y->child[1]==x)); 
        update(y);
      }
      //zig-zig or zag-zag 
      else if(y->child[0]==x&&z->child[0]==y){
        rotate(y,1);
        rotate(x,1);
        update(z);
      }
      else if(y->child[1]==x&&z->child[1]==y){
        rotate(y,0);
        rotate(x,0);
        update(z);
      }
      //zag-zig 
      else if(y->child[1]==x&&z->child[0]==y){
        rotate(x,0);
        rotate(x,1);
        update(y),update(z);
      }
      //zig-zag 
      else if(y->child[0]==x&&z->child[1]==y){
        rotate(x,1);
        rotate(x,0);
        update(y),update(z);
      }
    }
  }
  //当子节点发生变化的节点都需要被update到
  void update(Node *s){
    while(s!=NULL){
      int l=s->child[0]==NULL?0:s->child[0]->size;
      int r=s->child[1]==NULL?0:s->child[1]->size;
      if(s->size!=1+l+r) s->size=1+l+r;
      else break;
      s=s->pre;
    }
  }
  Node *find(int s){
    Node *p=root;
    while(p&&p->info!=s) p=p->child[p->info<s];
    return p;
  }
  //get the rank of node s
  int getRank(int s){
    Node *p=find(s);
    splay(p,root);
    return p->child[0]?p->child[0]->size+1:1;
  }
  //get the k-th node
  //@params 0<k<=st.size
  Node* getK(int k){
    Node *p=root;
    while(true){
      if(k<=0||k>p->size) return NULL;
      int l=p->child[0]?p->child[0]->size:0;
      if(k<=l) p=p->child[0];
      else if(k==l+1) return p;
      else p=p->child[1],k=k-l-1;
    }
    return p;
  }
  //get the left neighbor of s
  Node *getL(Node *s){
    assert(s==root&&s!=NULL);
    Node *p=s->child[0];
    while(p&&p->child[1]) p=p->child[1];
    return p;
  } 
  //get the right neighbor of s
  Node *getR(Node *s){
    assert(s==root&&s!=NULL);
    Node *p=s->child[1];
    while(p&&p->child[0]) p=p->child[0];
    return p;
  } 
  Node* insert(int s){
    Node *t=new Node(s);
    if(root==NULL) root=t;//注意root的pre保持NULL
    else{
      Node *p=root,*q;
      while(q=p->child[p->info<s]){ p=q;}
      //insert
      p->child[p->info<s]=t;
      t->pre=p;
      update(p);
      splay(t,NULL);
    }
    assert(t!=NULL&&root==t);
    return t;
  }
  //dfs
  void dfs(Node *s,void (*func)(Node *node)){
    if(s==NULL) return;
    dfs(s->child[0],func);
    func(s);
    dfs(s->child[1],func);
  } 
};
SplayTree st;
int main(){
  int s;
  int sum=0;
  int min=99999;
  int n; 
  scanf("%d",&n);
  while(n-->0){
    scanf("%d",&s);
    Node *t=st.insert(s);
    Node* l=st.getL(t),*r=st.getR(t);
    if(l) min=s-l->info;
    if(r) min=min<r->info-s?min:r->info-s;
    if(!l&&!r) min=s;
    sum+=min; 
  }
  st.dfs(st.root,print);
  printf("%d\n",sum);
  return 0;
}
//echo "7 11 10 12 13 9 88 100" | ./splay.exe
// echo "11 11 111 1111 2 3 10 12 13 9 88 100" | ./splay.exe
