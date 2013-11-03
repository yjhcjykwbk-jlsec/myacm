第三题：n*m矩阵填充
mask=2^m-1
int getNext(int i){   //L0[0]=L0[n+1]=mask(设定边界都是填充满了的）
      F= mask & (~(I0[i] | I0[i-1])) 
      ....枚举1*2的板子放法...有2^t种
      return 0 -> F
} 
for i=1->N+1:
  for f1=getNext(i-1):
    Ii-1=I0[i-1]+f1 //对第i-1行的Ii-1状态进行向后递推
    for f2=getNext(i):
      Ii=I0[i]+f2  //从I1-1递推到Ii状态，下面统计计数
      for j=0->D:
          for k=0->D-j:
            N[i%2][Ii][j+k]+=N[(i-1)%2][Ii-1][j]*S[Ii-1][f2][k] 
            //S记录的是第i-1行最初为Ii-1,保留k个空格，下一行填f2的方法数
for i=C->D:
   res+=N[(n+1)%2][0][i] //最后一行填0
return res
