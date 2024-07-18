//N queens M rooks
#include<stdio.h>
int n,m;
int digLeft[20];//col+row
int digRight[20];//col-row+n
int coll[10];//col
int RookdigLeft[20];//col+row
int RookdigRight[20];//col-row+n
int grid[10][10];
int solutions;

void queen(int row, int queens, int rooks){
    if(row==n+m){
        solutions++;
        // for(int i=0; i<n+m; i++){
        //     for(int j=0; j<n+m; j++){
        //         printf("%d ", grid[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    else{
        for(int col =0; col <n+m; col ++){
            if(queens<n){
                if(!RookdigLeft[col+row] && !RookdigRight[col-row+n] && !digLeft[col+row] && !digRight[col-row+n] && !coll[col]){
                    digLeft[col+row] = digRight[col-row+n] = coll[col] = 1;
                    grid[row][col] = 1;
                    queen(row+1, queens+1, rooks);
                    grid[row][col] =0;
                    digLeft[col+row] = digRight[col-row+n] = coll[col] = 0;
                }
            }
            if(rooks<m){
                if(!digLeft[col+row] && !digRight[col-row+n] && !coll[col]){
                    RookdigLeft[col+row]++;
                    RookdigRight[col-row+n]++;
                    coll[col] = 1;
                    grid[row][col] = 2;
                    queen(row+1, queens, rooks+1);
                    grid[row][col] = 0;
                    RookdigLeft[col+row]--;
                    RookdigRight[col-row+n]--;
                    coll[col] = 0;
                }
            }
        }
    }
}

int main()
{
    while(scanf("%d %d", &n, &m)!= EOF)
    {
        solutions = 0;
        queen(0,0,0);
        printf("%d\n", solutions);
    }
    return 0;
}