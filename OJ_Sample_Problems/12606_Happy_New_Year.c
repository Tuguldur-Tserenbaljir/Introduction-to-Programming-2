#include <stdio.h>
int main(){
    int n,a,b;
    scanf("%d%d",&n,&a);
    int l = 0;
    int r = 0;
    /*
     n -> number of friends
     a -> Bob house coordinate
     */
    while (n--){
        scanf("%d", &b);
        //b -> friend house coordinate
        if(b-a > r) r = b-a;
        if(a-b > l) l = a-b;
    }
    printf("%d\n",l*2+r*2);
}
