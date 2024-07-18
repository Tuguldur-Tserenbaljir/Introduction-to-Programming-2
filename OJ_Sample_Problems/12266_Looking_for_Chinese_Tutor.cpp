#include<iostream>
#include<map>
#include<string>

using namespace std;

int main(){
    map<string,string> wiki;
    wiki.insert(pair<string,string>("Wa", "Waninoko"));
    wiki.insert(pair<string,string>("Mi", "Milotic"));
    wiki.insert(pair<string,string>("Ma", "Magikarp"));
    wiki.insert(pair<string,string>("Va", "Vaporeon"));
    wiki.insert(pair<string,string>("Sh", "Sharpedo"));
    wiki.insert(pair<string,string>("Em", "Empoleon"));
    wiki.insert(pair<string,string>("La", "Lapras"));
    wiki.insert(pair<string,string>("Pi", "Pikachu"));
    wiki.insert(pair<string,string>("Pe", "Pikachu"));
    wiki.insert(pair<string,string>("Me", "Mega Gyarados"));
    wiki.insert(pair<string,string>("Tapu", "Tapu Fini"));

    int n;
    cin>>n;
    string name;
    string school;
    map <string,string>::iterator it;
    for(int i=1; i<=n; i++){
        cin>>name>>school;
        if(name[0]=='T'){
            it = wiki.find(name.substr(0,4));
        }
        else{
            it = wiki.find(name.substr(0,2));
        }
        if(it != wiki.end()){
            cout<<name<<" the "<<school<<" "<<it->second<<endl;
        }
        else{
            cout<<name<<" is looking for a Chinese tutor, too!"<<endl;
        }
    }
    return 0;
}