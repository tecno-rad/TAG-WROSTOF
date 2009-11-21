#include <string>
#ifndef effect_h
#define effect_h
using namespace std;
class Effect{

private:
	string target,effect_name,trigger_iftarget,trigger_iflauncher,status;
	int value;

public:
	Effect(string name,string targ,int value,string trigger_iflauncher="NULL",string trigger_iftarget="NULL");
	~Effect();
	string getTarget();
	string getName();
	string getTriggerIfTarget();
	string getTriggerIfLauncher();
};

Effect::Effect(string name,string targ,int val,string trigger_iflauncher,string trigger_iftarget){
	effect_name = name;
	target = targ;
	value = val;
	this->trigger_iflauncher=trigger_iflauncher;
	this->trigger_iftarget=trigger_iftarget;
}

Effect::~Effect(){}

string Effect::getTarget(){
	return target;
}

string Effect::getName(){
	return effect_name;
}
string Effect::getTriggerIfLauncher(){
	return trigger_iflauncher;
}

string Effect::getTriggerIfTarget(){
	return trigger_iftarget;
}
#endif