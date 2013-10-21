#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
#define MAXN 1000
int next[MAXN];
void getNext(char *p){
  //find p[0~i]'s longest qianzhui q
  //next[i] is the last index of q
  next[0]=-1;
  int i=1,l=strlen(p);
  while(i<l){
	int j=i-1;
	while(j>=0){
	  int l=next[j];
	  if(p[l+1]==p[i]) {next[i]=next[j]+1;break;}
	  j=next[j];	
	}
	//if p[0~i] did not find a qianzhui q
	//then next[i]=-1
	if(j<0) next[i]=-1;
	i++;
  }
  //next[i] set as the last index of a qianzhui q
  //and q 's last element != p[i]
  for(i=l-1;i>=1;i--){
	int j=next[i-1];
	while(p[j+1]==p[i]){
	  if(j<0) {next[i]=-1;break;}
	  j=next[j];
	}
	if(p[j+1]!=p[i]) next[i]=j+1;
  }
}
void kmp(char *t,char *p){
  getNext(p);
  int p1=0,p2=0; 
  int l1=strlen(t),l2=strlen(p);
		
  while(p2<l2&&p1<l1){
	while(p2>=0&&t[p1]!=p[p2])
	  p2=next[p2]; 
	//match succeed: s[p1]==p[p2]
	//p2 may be -1
	p1++,p2++;
  }	
  if(p2>=l2) cout<<"match succeed"<<endl;
  else cout<<"match failed"<<endl;
}
int main(){
  char s[1000],p[1000];
  FILE *f=fopen("test","r");
  while(true){
	fscanf(f,"%s\n",s); 
	fscanf(f,"%s\n",p); 
	cout<<s<<endl<<p<<endl;
	if(strcmp(s,"0")==0) break;
	kmp(s,p);
	for(int i=0;i<strlen(p);i++) printf("%d ",next[i]);
	cout<<endl;
  }
  return 1;
}
