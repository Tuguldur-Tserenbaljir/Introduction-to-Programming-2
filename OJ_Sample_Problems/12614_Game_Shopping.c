#include <stdlib.h>
#include <stdio.h>
int main(){
    int a[1000], b[1000];
    int game_index, wallet_index;
    int game_count = 0;
    scanf("%d%d",&game_index,&wallet_index);
    for(int i = 0 ; i<game_index;i++){
        scanf("%d", &a[i]);
    }
    for(int i = 0 ; i<wallet_index;i++){
        scanf("%d", &b[i]);
    }
    for(int i = 0; i<game_index; i++){
        if(game_count < wallet_index && b[game_count] >= a[i]){
            game_count = game_count + 1;
        }
    }
    printf("%d\n",game_count);
}
