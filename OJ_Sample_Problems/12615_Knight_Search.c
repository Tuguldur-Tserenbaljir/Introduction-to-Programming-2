#include<stdio.h>
#include<stdlib.h>
char fav[]={'I','C','P','C','A','S','I','A','S','G'};
char grid[105][105];
int n;
int dirRow[] = {1,-1,1,-1,2,-2,2,-2};
int dirCol[] = {2,2,-2,-2,1,1,-1,-1};
int check(int row, int col, int idx){
    if(idx==10){
        return 1;
    }
    for(int i=0; i<8; i++){
        if(row+dirRow[i]<n && row+dirRow[i]>=0 && col+dirCol[i]>=0 && col+dirCol[i]<n &&
           grid[row+dirRow[i]][col+dirCol[i]] == fav[idx]){
            if(check(row+dirRow[i],col+dirCol[i],idx+1) == 1) return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf(" %c", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for(int j = 0; j<n;j++){
            if(grid[i][j]=='I'){
                if(check(i,j,1) == 1){
                    printf("YES\n");
                    return 0;
                }
            }
        }
    }
    printf("NO\n");
    return 0;
}