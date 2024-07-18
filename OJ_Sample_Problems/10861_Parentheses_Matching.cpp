#include<iostream>
#include<string>
#include<stack>
using namespace std;

bool match(char L, char R){
    if(L == '(' && R == ')') return true;
    else if(L == '{' && R == '}') return true;
    else if(L == '[' && R == ']') return true;
    else if(L == '<' && R == '>') return true;
    else return false;
}

int main(){
    int q;
    cin>>q;
    bool error;
    string input;
    getline(cin,input);
    for(int i=1; i<=q; i++){
        error = false;
        stack<char> stacks;
        getline(cin,input);//scans input until '\n', doesnt include'\n'
        if(!input.empty()){
            for(string::iterator i = input.begin(); i != input.end(); i++){
                if(*i =='('|| *i == '{' || *i == '[' || *i == '<') stacks.push(*i);
                else if(stacks.empty() || !match(stacks.top(), *i)){
                    error = true;
                    break;
                }
                else{
                    if(!stacks.empty())stacks.pop();
                }
            }
        }
        if (!stacks.empty()) error = true;
        cout << "Case "<< i << ": ";
        if(error) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}