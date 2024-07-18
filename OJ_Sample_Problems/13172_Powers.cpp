#include<iostream>
//#include "function.h"
#include<string>
#include<cmath>
using namespace std;
//using std::pow;


class special_power{
public:
    int n;
    special_power(int n);
    int fpow(int x);
    int fpow(int x, int m);
    int fpow();
    string fpow(string s);
    string fpow(string s, int m);
};

/*
The 1st line, output the result of xn % 880301 //done

The 2nd line, output the result of xn % m //done

The 3rd line, output the result of 2n % 880301 //done

The 4th line, output the result of sn

The 5th line, output the result of sn % m */
//3 5 10 abcd

special_power::special_power(int n){
    this->n = n;
}
//4th line output the result of sn
string special_power::fpow(string s){
    int length = s.length();
    string dummy_string;
    for(int i = 0; i<length;i++){
        for(int j =0;j<this->n;j++){
            dummy_string += s[i];
        }
    }
    return dummy_string;
}
//5th line output the result of sn % m */
string special_power::fpow(string s, int m){
    string dummy_string;
    for(int i = 0; i<s.length();i++){
        for(int j =0;j<n;j++){
            if(i*this->n + j >=m) return dummy_string;
            dummy_string += s[i];
        }
    }
    return dummy_string;
}
//3rd line
int special_power::fpow(){
    int long long fpow = 1;
    for(int i =0;i<n;i++){
        fpow *= 2;
        fpow = fpow%880301;
    }
    return fpow%880301;
}
//The 2nd line, output the result of xn % m //done
//2nd line
int special_power::fpow(int x, int m){
    long long int fpow =1;
    for(int i = 0;i<n;i++){
        fpow *= x;
        fpow = fpow%m;
    }
    return fpow%m;
}
//1st line

//The 1st line, output the result of xn % 880301 //done
int special_power::fpow(int x){
    int long long fpow =1;
    for(int i =0;i<n;i++){
        fpow *= x;
        fpow = fpow%880301;
    }
    return fpow%880301;
}
