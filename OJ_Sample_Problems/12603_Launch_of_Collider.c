#include <stdlib.h>
#include <stdio.h>
  int main(){
      char s[200005];
      long long x,a[200005];
      int n;
      long long min=99999;
      scanf("%d",&n);
      scanf("%s", s); // n=3 L L R
        for(int i =0; i<n;i++){
            scanf("%lld",&a[i]);
        }

        for(int i = 0;i<n;i++){
            if( s[i] == 'L' && s[i-1] == 'R'){
                x = (a[i] - a[i-1])/2;
                if(x<min){
                    min = x;
                }
            }
        }
        if(min == 99999){
            printf("-1\n");
        } else{
            printf("%lld\n",min);
        }
        return 0;
}