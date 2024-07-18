    #include <stdlib.h>
    #include <stdio.h>
    int leap_year_checker();
    int main(){
        int days = 0;
        int n;
        int year;
        scanf("%d", &n);
        while(n--) {
            days = 0;
            scanf("%d", &year); //2016
            //printf("%d\n", leap_year_checker(year));
            if(leap_year_checker(year)){
                while(!(leap_year_checker(year) && days%7==0) || days == 0){
                    year++; //2017 , 2018 2019 2020
                    days += leap_year_checker(year) + 1; //days = 1, days = 2, days = 4
                }
                printf("%d\n", year);
            }
            else{
                while ( !(leap_year_checker(year) == 0 && days%7 == 0) || days == 0 ){
                    year++;
                    days += leap_year_checker(year) +1;
                }
                printf("%d\n", year);

            }
        }
    }

    int leap_year_checker(year){
        if ((year%4 == 0 && year%100 != 0) || year%400 == 0){
            return 1;
        }else return 0;
    }
