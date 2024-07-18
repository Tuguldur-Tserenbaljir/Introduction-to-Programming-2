#include <stdlib.h>
#include <stdio.h>
int leap_year_checker();
int main(){
    int year;
	scanf("%d", &year);
	printf("%s\n", leap_year_checker(year));
}

int leap_year_checker(year){
    if ((year%4 == 0 && year%100 != 0) || year%400 == 0){
        return "Leap year";
    }else return "Common year";
}