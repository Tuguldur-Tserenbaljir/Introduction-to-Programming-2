#include<stdio.h>
#include<stdlib.h>
int k;
long long l,r,temp,level[55];
void ouq(int k);
void findlen(int k);
int main(){
    while (scanf("%d %lld %lld",&k,&l,&r) != EOF){
        temp = 0;
        findlen(k);
        ouq(k);
        printf("\n");
    }
    return 0;
}
void ouq(int k){
    if(temp+level[k]<=l){
        temp+=level[k];
        return;
    }
    else{
        if(temp>=l && temp<=r) printf("O");//base case

        temp++;

        if(k!=1 && temp<=r) ouq(k-1);

        if(temp>=l && temp<=r) printf("u");//base case

        temp++;

        if(k!=1 && temp<=r) ouq(k-1);

        if(temp>=l && temp<=r) printf("Q");//base case

        temp++;
    }

}
void findlen(int k){
    level[0] = 0;
    for(int i = 0 ; i<k;i++){
        level[i+1] = 3 + 2*level[i];
    }
}