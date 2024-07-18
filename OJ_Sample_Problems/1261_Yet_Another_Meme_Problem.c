#include <stdlib.h>
#include <stdio.h>
    int main(){
    long long a,b;
    int n ;
    scanf("%d", &n);
    while(n--){
        int res = 0;
        int num = 9;
        scanf("%lld%lld", &a,&b);
        while(b>=num){
            num = num*10+9;
            res++;
        }
        printf("%lld\n",a*res);
    }
}