#include <iostream>
#include <stdio.h>
#include <string>
#include "function.h"
using namespace std;



Polynomial::Polynomial(){
    greatestPower = 0;
    for(int i=0; i<101; i++){
        coefficients[i] = 0;
    }
}

Polynomial::Polynomial(const int greatestpower, const int coefficient[51]){
    greatestPower = greatestpower;
    for(int i = 0; i<=greatestPower;i++){
        coefficients[i] = coefficient[i];
    } 
}

Polynomial Polynomial::add( const Polynomial b) const{
    Polynomial ans = Polynomial();
    ans.greatestPower = max(this->greatestPower,b.greatestPower);
    for(int i = 0; i<=ans.greatestPower;i++){
        ans.coefficients[i] = this->coefficients[i] + b.coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::subtract( const Polynomial b) const{
    Polynomial ans = Polynomial();
    ans.greatestPower = max(this->greatestPower,b.greatestPower);
    for(int i = 0; i<=ans.greatestPower;i++){
        ans.coefficients[i] = this->coefficients[i] - b.coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::multiplication( const Polynomial b) const{

    Polynomial ans = Polynomial();
    ans.greatestPower = this->greatestPower + b.greatestPower;
    for(int i = 0; i<=this->greatestPower;i++){
        for(int j = 0 ; j<=b.greatestPower;j++){
            ans.coefficients[i+j] += this->coefficients[i] * b.coefficients[j];
        }
    }
    return ans;
}

void Polynomial::output() const {
    for(int i= greatestPower; i>=0 ;i--){
        if(i==0){
            cout<<coefficients[i];
        }
        else {
            cout<<coefficients[i]<<" ";
            }
    }
}