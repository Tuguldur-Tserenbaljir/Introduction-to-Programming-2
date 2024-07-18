#include<stdio.h>
#define REP(i,j,k) for(int i=j;i<k;i++)
int m,l,r,k;
char s[10005],ss[10005];
main(){
    scanf("%s%d",&s,&m);
    while(m--){
        scanf("%d%d%d",&l,&r,&k), l--, r--;
        REP(i,l,r+1) ss[l+(i-l+k)%(r-l+1)] = s[i];
        REP(i,l,r+1) s[i] = ss[i];
    }
    printf("%s\n",s);
}