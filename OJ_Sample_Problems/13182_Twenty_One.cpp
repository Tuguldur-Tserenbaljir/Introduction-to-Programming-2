#include <iostream>
#include <string>
//#include "function.h"
using namespace std;


class Guest {
public:
	Guest();
	Guest(string s, int m, int ski);
	~Guest();
	string get_name();
	int get_money();
	int get_skill();
	void Win(int m);
	
private:
	string name;
	int money;
	int skill;
};
//Guest <Someone> <Money> <Skill> 
Guest::~Guest(){

}
Guest::Guest(){
	name = '\0';
	money = 0;
	skill = 0;
}
Guest::Guest(string s, int m, int ski){
	name = s;
	money = m;
	skill = ski;
}
string Guest::get_name(){
	return name;
}
int Guest::get_money(){
	return money;
}
int Guest::get_skill(){
	return skill;
}
void Guest::Win(int m){
	money += m;	
}
	

class Casino {
public:
	Casino();
	~Casino();
	void Enterance(int f);
	void GuestEnter(string s, int m, int ski);
	void Win(string s, int m);
	void EndDay();
	void Result();
	
private:
	int fee;
	
	int guest_num;
	Guest *guest[1009];
	
	int income;
	int list_num;
	string blacklist[1009];
};
Casino::~Casino(){
	for(int i=0; i<guest_num;i++){
		delete guest[i];
	}
	guest_num = 0;
}

Casino::Casino(){
	fee = 0;
	guest_num = 0;
	// for(int i = 0 ;i<1009;i++){
	// 	guest[i] = 0;
	// }
	// for(int i=0; i<1009; i++){
	// 	blacklist[i] = '\0';
	// }
	income =0;
	list_num =0;
}
//Check if all are blacklisted or not
//they are already in the casino, check the guestlist and directly return if they are there
//how much money they bring, if they dont meet the fee take their money and blacklist them
// else they are just a new guest 
void Casino::Enterance(int f){
	fee = f;
}
void Casino::GuestEnter(string s, int m, int ski){
	for(int i = 0;i<list_num;i++){
		if(s == blacklist[i]) return;
	}

	for (int i = 0; i < guest_num; i++)
	{
		if (s == guest[i]->get_name()) return;
	}

	if(m <= fee){
		income +=m;
		blacklist[list_num] = s;
		list_num++;
	}
	else{
		guest[guest_num] = new Guest(s,m-fee,ski);
		guest_num++;
		income += fee;
	}
}
//check if they are in the blacklist or not
//check if amount is no more than the skiX2
//if they win more than skiX2 add blacklist and give them the money
//if they the money they win is less than or equal to 0 they blacked
void Casino::Win(string s, int m){
	for(int i = 0; i<list_num;i++){
		if(s == blacklist[i]) return;
	}
	for(int i = 0; i<guest_num;i++){
		if(guest[i]->get_name() == s){
			if(guest[i]->get_skill()*2 < m){
				guest[i]->Win(m);
				income = income - m;
				blacklist[list_num] = s;
				list_num++;
				return;
			}
			else if(guest[i]->get_money() + m <= 0){
				income = income + guest[i]->get_money();
				blacklist[list_num] = s;
				list_num++;
				return;
			}else{
				income = income -m;
				guest[i]->Win(m);
				return;
			}
		}
	}
}
void Casino::EndDay(){
	for (int i = 0; i < guest_num; i++)
	{
		delete guest[i];
	}
	guest_num = 0;
}
void Casino::Result(){
	//blacklist
	cout<<income<<endl;
	for(int i =0;i<list_num;i++){
		cout<<blacklist[i]<<"\n";
	}
}