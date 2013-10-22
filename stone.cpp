bool 
judge(n,m)//判断能否先手胜,m为最多能取的数字 
{
  if(m>=n) return true;
  int k=n/m,s=n%m;//n=k*m+s
  loop(i,1,min(m,n/3)){
    takeout(i);
    if(!judge(n-i)) return true;
  }
  return false;
}
