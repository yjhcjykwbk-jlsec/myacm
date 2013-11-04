#include "test.h"
#include <string.h>
#include <stack>
inline int getPriority(char a){
  switch(a){
    case '+':case '-':return 1;
    case '*':case '/': return 2;
    case '(':return 3;
    case ')':return 0;
    case '#':return 0;
    default: 
    assert(1);return  -1;
  }
}
int fn(int a,int b,char c){
  cout<<a<<c<<b<<endl;
  switch(c){
    case '+':return a+b;case '-':return a-b;
    case '*':return a*b;case '/':return a/b;
    default:
    assert(1);return 0;
    }
}

inline int cmp(char a,char b){
  return getPriority(a)-getPriority(b);
}
int calc(const char *str){
  stack<int> num_st;
  stack<char> st;
  rep(i,0,strlen(str)-1){
    cout<<i<<":"<<str[i]<<endl;
    if(isdigit(str[i])){
      int j=i;
      while(isdigit(str[j])) j++;
      char *t=(char*)malloc(MAXN);
      strncpy(t,str+i,j-i); 
      int s;
      sscanf(t,"%d",&s);
      num_st.push(s);
      i=j-1;
    }else{
      while(!st.empty()){
        char s=st.top();
        if(s=='('&&str[i]==')'){ st.pop();break;}
        else if(cmp(str[i],s)<=0&&s!='('){
          int b=num_st.top();num_st.pop();
          int a=num_st.top();num_st.pop();
          int c=fn(a,b,s); 
          num_st.push(c);
          st.pop();
        }
        else break;
      }
      if(str[i]!=')') st.push(str[i]);
    }
  }
  return num_st.top();
}

int main(){
  char *str="1+2*(3-1/2+4*5)/4-6#";
  cout<<calc(str);
  return 0;
}
          



