第九题的递推方程：
func(i,k)：
 // 对于sum[i-1][k-1]->sum[i][k]的递推，
 //含义是从前i-1个数找k-1个数，再加入第i个数，组成k组合。计算这些组合异或值的和。
  change=0
  for j=0 TO 31:
    对于n[i]的二进制第j位（j=0~..) ,值为w（w=0或1）

    前i-1个数里j位为1的有l=num[i-1][j]个，为0的有r=(i-1)-l个。因此所有k-1组合中包含偶数个1的组合个数：
    s=C<l,0>*C<r,k-1>+C<l,2>*C<r,k-3>.....C<l,2*p>*C<r,k-1-2*p>
    奇数个1的组合个数为t=C<i-1,k-1>-s

    因此,把第i个数添加进上述每个k-1组合，将会带来变化为：change+=(2*w-1) * 2^j * (s-t)

  return sum[i-1][k-1]+change

