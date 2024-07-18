#include <string>
#include <iostream>
#include <cstring>
#include<sstream>
//#include "function.h"
using namespace std;
class Human {
public:
 string name;
 int money;
 int skill;
 bool kicked;
 int cards;
 int bets;

 Human(string n, int m, int ski);
 
 virtual void Pay(Human *human) = 0;
 virtual void Bet() {}
 virtual void Draw() {}
 virtual bool Kicked() {}
 virtual int Win(Human *human) {}
 virtual bool Bankrupt() {}
 virtual void Kick(Human *human, int flag) {}
 virtual bool Cheat(Human *human) {}
 int get_money();
 ~Human();
};

Human::Human(string n, int m, int ski){
    name = n;
    money = m;
    skill = ski;
    cards = 0;
    bets = 0;
    kicked = false;
}

int Human::get_money(){
    return money;
}

Human::~Human(){

}

class Guard : public virtual Human {
public:
 Guard(int ski);
 void Pay(Human *human);
 void Kick(Human *human, int flag);
 ~Guard(); 
};
//299
Guard::Guard(int ski):Human("Guard", 0, ski){}

void Guard::Pay(Human *human){
    if(this->skill < human->skill){
        human->money += (human->skill - this->skill);
        this->money -= (human->skill - this->skill);
    }
}
//flag 0 = player bankrupt
//flag 1 = player cheater
void Guard::Kick(Human *human, int flag){
    if(flag == 1){
        human->kicked = true;
        this->Pay(human);
    }
    else{
        human->kicked = true;
    }
}
Guard::~Guard(){

}



class Banker : public virtual Human {
public:
 Banker(int ski);
 void Pay(Human *human);
 int Win(Human *human);
 void Draw();
 ~Banker();
};
Banker::Banker(int ski):Human("Banker", 0, ski){}
void Banker::Pay(Human *human){

    if(human->kicked==1) return;

    if(human->name == "Guard"){
        this->money -= 100;
        human->money += 100;
        return;
    }
  
    int total = human->bets;//the amount of bet that player sets
    if(human->skill < this->skill){
        int bonus = human->cards * 10;
        total += bonus; // total = bets + bonus

    }
    if(human->cards == 21){
        total = 2*total;
    }
    this->money -= total;
    human->money += total;
 this->bets = total;
}
int Banker::Win(Human *human){
    if(this->cards > 21 && human->cards > 21){
        return 2;//when its a draw, when both loses
    }
    else if(human->cards <=21 && (this->cards <  human->cards || this->cards > 21)){
        return 0; // player win
    }
    else{
        return 1; // player lose
    }
    return 1;
}
void Banker::Draw(){
    string card_string;
    this->cards =0;
    while(card_string.empty()) getline(cin, card_string);
    istringstream input_stream(card_string);
    int card =0;
    while(input_stream >> card){
        this->cards += card;
    }
}
Banker::~Banker(){}







class Player : public virtual Human {
public:
 Player(string name, int m, int ski);
 void Pay(Human *human);
 void Bet();
 void Draw();
 bool Kicked();
 bool Bankrupt();
 bool Cheat(Human *human);
 ~Player();
};
//cin >> name >> player_money >> player_skill;

Player::Player(string name, int m, int ski):Human(name, m, ski){}

void Player::Pay(Human *human){
    if(this->bets >= this->money){
        human->money += this->money;
        this->money -= this->money;
    }else{
        this->money -= this->bets;
        human->money += this->bets;
    }
    return;
}

void Player::Bet(){
    string temp_name;
    while(temp_name.empty()) getline (cin, temp_name);
    istringstream input(temp_name);
    input>>name;
    input>>this->bets;
}

void Player::Draw(){
    string card_string;
    this->cards =0;
    while(card_string.empty()) getline(cin, card_string);
    istringstream input_stream(card_string);
    int card =0;
    while(input_stream >> card){
        this->cards += card;
    }
}

bool Player::Kicked(){
    return kicked;
}
bool Player::Bankrupt(){
    if(this->money <= 0){
        return 1;
    }else{
        return 0;
    }
}
bool Player::Cheat(Human *human){
    if(2 * this->skill < human->bets){
        return 1;
    }
    else{
        return 0;
    }
}
Player::~Player(){}