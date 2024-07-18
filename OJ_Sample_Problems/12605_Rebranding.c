#include<stdio.h>
int alph[27];
char s[200005];

void change(int x, int y){
    for(int i=0; i<26; i++){
        if(alph[i]==x) alph[i] = y;
        else if(alph[i]==y) alph[i] = x;
    }
    return;
}

int main()
{
    int init, designers;
    scanf("%d %d", &init, &designers);
    scanf("%s", s+1);
    for(int i=0; i<26; i++){
        alph[i]='a'+ i;
    }
    for(int i=0; i<designers; i++){
        char x,y;
        scanf(" %c %c", &x, &y);
        change(x,y);
    }
    for(int i=1; i<=init; i++){
        printf("%c", alph[s[i]-'a']);
    }
    printf("\n");

    return 0;
}