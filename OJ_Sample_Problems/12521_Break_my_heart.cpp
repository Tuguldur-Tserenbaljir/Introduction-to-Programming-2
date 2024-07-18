#include<iostream>
#include <set>

using namespace std;

int main(){
    set<int>sets;
    int n;
    cin>>n;
    string instructions;
    while(n--){
        cin>>instructions;
        if(instructions == "insert"){
            int val;
            cin>>val;
            sets.insert(val);
        }
        else if(instructions == "print"){
            if(sets.size() == 0)continue;
            for(set<int>::iterator it = sets.begin(); it !=sets.end(); it++){
                if(it != sets.begin())cout<<" ";
                cout<< *it;
            }
            cout<<endl;
        }
        else if(instructions == "min"){
            if(sets.size() == 0) continue;
            cout<< *(sets.begin())<<endl;
        }
        else if(instructions == "range_erase"){
            int l,r;
            cin>>l>>r;
            set<int>::iterator low = sets.lower_bound(l);
            set<int>::iterator up = sets.upper_bound(r);
            sets.erase(low,up);
        }
    }
}