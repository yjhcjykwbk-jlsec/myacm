#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
bool map[102][302],visit[302];
int link[302];
int p,n;
bool dfs(int u)
{
    int i;
    for(i=1;i<=n;i++)
        if(map[u][i]&&!visit[i])
        {
            visit[i]=true;
            if(link[i]==-1||dfs(link[i]))
            {
                link[i]=u;
                return true;
            }
        }
    return false;
}
int main()
{
    int CASE,i,k,j,sum;
    scanf("%d",&CASE);
    while(CASE--)
    {
        memset(map,0,sizeof(map));
        scanf("%d%d",&p,&n);
        for(i=1;i<=p;i++)
        {
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&j);
                map[i][j]=true;
            }
        }
        sum=0;
        memset(link,-1,sizeof(link));
        for(i=1;i<=p;i++)
        {  memset(visit,0,sizeof(visit));
            if(dfs(i))sum++;
        }
        if(sum>=p)
        printf("YES\n");
        else printf("NO\n");

    }
    return 0;
}
