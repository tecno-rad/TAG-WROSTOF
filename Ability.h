#include "Effect.h"
#include <vector>
#include "ClassConsts.h"
using namespace std;
#ifndef ability_h
#define ability_h
class Ability{
private:
	string id,name,description;
	int level;
	unsigned int classmask,type;
	int delay;
	vector<Effect> effects;
public:
	Ability(string id,string name,string description,vector<Effect> effects,unsigned int type,int level=1,unsigned int classmask=ALL,int delay=0);
	~Ability();
	void addEffect(Effect effect);
	void setLevel(int offset=1);
	string getDescription();
	string getId();
	string getName();
	int getDelay();
	void setDelay(int delay);
	vector<Effect> getEffects();
	bool isForClass(unsigned int classconst);
	int getType();
	
};

Ability::Ability(std::string id, std::string name, std::string description,vector<Effect> effects,unsigned int type,int level,
				 unsigned int classmask, int delay){
    this->id = id;
	this->name = name;
	this->description = description;
	this->effects = effects;
	this->type = type;
	this->level = level;
	this->classmask = classmask;
	this->delay = delay;
}

Ability::~Ability(){
	this->effects.~vector();
}

void Ability::addEffect(Effect effect){
	this->effects.push_back(effect);
}

void Ability::setLevel(int offset){
	this->level += offset;
}

string Ability::getDescription(){
	return this->description;
}

string Ability::getId(){
	return this->id;
}

string Ability::getName(){
	return this->name;
}
	
int Ability::getDelay(){
	return this->delay;
}

void Ability::setDelay(int delay){
	this->delay = delay;
}

vector<Effect> Ability::getEffects(){
	return this->effects;
}
/* 
   bitwise AND between input class constant and the ability mask to check if
   ability is suitable for the input class.
   	
	example: ability set for TECH and SOLDIER
	ABILITY MASK: 000001001
	we check if is suitable for TECH
	TECH: 000001000
	MASK & TECH = 000001000 = 256 >= 1 OK.
	otherwise, if we check for SNIPER
	SNIPER: 100000000
	MASK & SNIPER = 00000000 = 0 < 1 FAILS.

*/
bool Ability::isForClass(unsigned int classconst){
	return (classmask & classconst)>=1;
}
#endif