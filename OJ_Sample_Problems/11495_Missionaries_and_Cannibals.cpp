#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>

using std::vector;
using std::set;
using std::list;
using std::cout;
using std::endl;

// A state contains five components:
// The first two components denote the current numbers of
// missionaries and cannibals at the left bank of the river.
// The third and fourth components denote the current numbers
// of missionaries and cannibals at the right bank.
// The fifth component denotes the location of the boat:
// 1 means "left bank" and -1 means "right bank".
using State = vector<int>;
class Crossing
{
private:
    vector<int> _npeople;  // how many missionaries and cannibals
                           // we use vector<int> as a tuple (int, int)
                           // the first integer indicate the number of missionaries
                           // the second integer indicates the number of cannibals
    set<list<State>> _paths;  // trial paths in progress
    set<State> _explored;     // explored states
    set<list<State>> _solutions;
public:
    // specify the numbers of missionaries and cannibals
    Crossing(vector<int> np): _npeople {np} { }
    // the starting porint of your implementation
    void solve();
    // extend to other possible states from a certain state
    set<State> extend(State s);
    // may use s[4] to indicate the direction of move
    State Go(State s, int missionary, int cannibal);
    // check the validity of a state
    bool valid(State s);
    // check if all people are at the right bank
    bool found(State s);
    void show_solutions() {
        for (auto path : _solutions) {
            for (auto s : path) {
                if (!s.empty()) {
                    cout << "(" << s[0] << ", " << s[1] << ")";
                    cout << "(" << s[2] << ", " << s[3] << ")";
                    if (s[4]==1) cout << " left\n";
                    else cout << " right\n";
                }
            }
            cout << "done" << endl;
        }
    }
};

void Crossing::solve(){
    list<State> IP;
    IP.push_back({_npeople[0], _npeople[1], 0, 0, 1});
    _paths.insert(IP);//inserts the initial state to _paths
    while(!(_paths.empty())){
        set<list<State>> newPaths;
        set<list<State>> oldPaths;
        for(auto p : _paths){ //look through the lists of _paths
            _explored.insert(p.back()); //inserts the current/last state of linked list p
            auto nextStates = extend(p.back()); //creates an iterator that goes through the possible states from s
            for(auto x : nextStates){
                if(found(x)){
                    auto np = p; // creates an iterator that points to a list of states identical to the current list
                    np.push_back(x); // inserts one more state, s, which is the final product/answer
                    _solutions.insert(np); //add linked list np to the solutions
                }
                else{
                    auto search = _explored.find(x); // creates an iterator that points to a set of states similar to x
                    if (search == _explored.cend()) { //if find function finds nothing, it will return cend()
                        auto np = p; //creates an iterator that points to a list of states identical to the current list
                        np.push_back(x); // inserts one more state, s, which is the final product/current state
                        newPaths.insert(np); //add linked list np to the new paths to be traversed
                    }
                }
            }
            oldPaths.insert(p); //puts the current state into an old paths list to be deleted.
        }
        for (auto p : oldPaths)_paths.erase(p); //erases all paths that have been traversed in this loop
        for (auto p : newPaths)_paths.insert(p); //adds all new paths to be traversed
    }
    return;
}

set<State> Crossing::extend(State s){ //creates a tree of possible states stemming from s
    set<State> nextStates;
    for (int m=0; m <= _npeople[0]; m++) {
        for (int c=0; c <= _npeople[1]; c++) {
            // a boat can take one or two people
            if (m+c>=1 && m+c<=2) {
                State ss = Go(s, m, c);
                if (valid(ss)) nextStates.insert(ss);
            }
        }
    }
    return nextStates;
}


State Crossing::Go(State s, int missionary, int cannibal){
    s[0] = s[0] - s[4]*missionary;
    s[1] = s[1] - s[4]*cannibal;
    s[2] = s[2] + s[4]*missionary;
    s[3] = s[3] + s[4]*cannibal;
    s[4] = -s[4];
    return s;
}

bool Crossing::valid(State s){
    if(s[0] < 0 || s[1] < 0 || s[2] < 0 || s[3] < 0) return false;
    if((s[0] < s[1] && s[0]!= 0) || (s[2] < s[3] && s[2]!=0)) return false;
    return true;
}

bool Crossing::found(State s){
    if(s[0] == 0 && s[1] == 0 && s[2] == _npeople[0] && s[3] == _npeople[1]) return true;
    return false;
}
