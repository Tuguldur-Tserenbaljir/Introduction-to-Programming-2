#include<iostream>
#include<deque>
#include<queue>


using namespace std;
int main(){
    string cmd;
    int arg;
    queue<string>q;
    while(cin>>cmd){
        if(cmd == "Pop"){
            if(q.empty())continue;
             q.pop();
        }
        else if(cmd == "Front"){
            if(q.empty())cout<<"empty"<<endl;
            else{
                cout<<q.front()<<endl;}
        }
        else{
            string name;
            cin>>name;
            q.push(name);
        }
    }

}
//PUSH BRUCE