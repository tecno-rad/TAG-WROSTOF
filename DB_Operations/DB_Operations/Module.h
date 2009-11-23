#include "ClassConsts.h"
#ifndef module_h
#define module_h
#define COCKPIT 1
#define LEGS 2
#define ARMS 3
#include <string>
using namespace std;

class Module{
private:
	int type,energyMaxBonus,speedBonus,shieldBonus,accuracyBonus;
	unsigned int classmask;
	string name,description;
	double sellPrice,buyPrice;
public:
	Module();
	Module(string name,int type,double price,unsigned int classmask=ALL);
	Module(string name,int type,unsigned int classmask,string description,int energyBonus=0,
		int speedBonus=0,int shieldBonus=0,int accuracyBonus=0);
	~Module();
	int getType();
	int getEnergyMaxBonus();
	int getSpeedBonus();
	int getAccuracyBonus();
	int getShieldBonus();
	string getName();
	string getDescription();
	double getBuyPrice();
	void setBuyPrice(double price);
	double getSellPrice();
	void setSellPrice(double price);
	bool isForClass(unsigned int classconst);
};

Module::Module(){

}

Module::Module(string name,int type,double price,unsigned int classmask){
	this->name = name;
	this->type = type;
	this->buyPrice = price;
	this->sellPrice = price/2.0;
	this->classmask = classmask;
}


Module::Module(string name,int type,unsigned int classmask,string description,int energyMaxBonus,
		int speedBonus,int shieldBonus,int accuracyBonus){
	this->type = type;
	this->classmask = classmask;
	this->name = name;
	this->description = description;
	this->energyMaxBonus = energyMaxBonus;
	this->speedBonus = speedBonus;
	this->shieldBonus = shieldBonus;
	this->accuracyBonus = accuracyBonus;
}

Module::~Module(){}

int Module::getType(){
	return this->type;
}

int Module::getEnergyMaxBonus(){
	return this->energyMaxBonus;
}

int Module::getShieldBonus(){
	return this->shieldBonus;
}

int Module::getSpeedBonus(){
	return this->speedBonus;
}

int Module::getAccuracyBonus(){
	return this->accuracyBonus;
}

string Module::getName(){
	return this->name;
}

string Module::getDescription(){
	return this->description;
}

double Module::getBuyPrice(){
	return this->buyPrice;
}

void Module::setBuyPrice(double price){
	this->buyPrice = price;
}

double Module::getSellPrice(){
	return this->sellPrice;
}

void Module::setSellPrice(double price){
	this->sellPrice = price;
}

/* 
   bitwise AND between input class constant and the module mask to check if
   module is suitable for the input class.
   	
	example: module set for TECH and SOLDIER
	MODULE MASK: 000001001
	we check if is suitable for TECH
	TECH: 000001000
	MASK & TECH = 000001000 = 256 >= 1 OK.
	otherwise, if we check for SNIPER
	SNIPER: 100000000
	MASK & SNIPER = 00000000 = 0 < 1 FAILS.

*/
bool Module::isForClass(unsigned int classconst){
	return (classmask & classconst)>=1;
}
#endif