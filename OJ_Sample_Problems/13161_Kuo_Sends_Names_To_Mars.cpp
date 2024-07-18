#include<string>
#include<stdlib.h>
#include<iostream>

using namespace std;

int main(){
    string name;
    cin>>name;
    int l = name.length()-1;
    int count = 0;
    for(int i = 0; i<l;i++){
        if (name[i] == '1')
        {
            ++i;
        }
        
        if(name[i] == name[i+1]  && name[i+1] != '1'){
           name[i+1] = '1';
           count++;
            if(name[i] == name[i+2] && name[i+2] != '1'){
                name[i+2] = '1';
                count++;
            }
        }
        else if(name[i] == name[i+2] && name[i+2] != '1'){
            name[i+2] = '1';
            count++;
        }
    }
    cout<<count<<endl;
    return 0;
}