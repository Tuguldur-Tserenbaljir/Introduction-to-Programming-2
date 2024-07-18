
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;
using std::deque;
int main(){
    deque<int> country[3];
    deque<int> list;

    int N;
    cin>>N;
    string cmd;
    for(int i=1; i<=N; i++){
        //cout<<i<<endl;
        cin>>cmd;
        //cout<<cmd;
        if(cmd == "ENQUEUE"){
            int val; 
            cin>>val;
            if(val%3==0){
                if(country[0].empty()) list.push_back(0);
                country[0].push_back(val);
                //cout<<"cek";
            }
            else if(val%3==1){
                if(country[1].empty()) list.push_back(1);
                country[1].push_back(val);
            }
            else if(val%3==2){
                if(country[2].empty()) list.push_back(2);
                country[2].push_back(val);
            }
        }
        else if(cmd == "DEQUEUE"){
            cout<<*country[*list.begin()].begin()<<endl;
            country[*list.begin()].pop_front();
            if(country[*list.begin()].empty()) list.pop_front();
            
        }
    }

    return 0;
}