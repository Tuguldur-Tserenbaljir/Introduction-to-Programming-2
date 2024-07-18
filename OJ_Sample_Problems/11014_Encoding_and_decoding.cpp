//#ifndef _FUNC_H
//#define _FUNC_H
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }

    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }
private:
    bool encoded;
    std::string code_str;
};

using namespace std;
void RleCodec::encode(){
    stringstream ss;
    int count = 0;
    char temp = code_str.front();
    for(auto c : code_str){
        if(c == temp){
            count++;
        }
        else{
                if(count == 1){
                    ss<<temp;
                }
                else if(count == 2){
                    ss<<temp<<temp;
                }
                else if(count >2){
                    ss<<count<<temp;  
                }
                temp = c;
                count = 1;  
        }
    }
    
        if(count == 1){
            ss<<temp;
        }else if(count == 2){
            ss<<temp<<temp;
        }
        else if(count>2){
            ss<<count<<temp;
        }
        code_str = ss.str();
        encoded = true;

}


void RleCodec::decode(){
    stringstream ss;
    stringstream int_ss;
    for(auto c : code_str){
        if(isdigit(c)){
            int_ss << c;
        }
        else if(isalpha(c)){
            int count = 0;
            int_ss>>count;
            if(count == 0){
                ss<<c;
            }
            else{
                while(count--){
                    ss<<c;
                }
            }
            
            int_ss.str("");
            int_ss.clear();
        }
    }   
    code_str = ss.str();
    encoded = false;
}