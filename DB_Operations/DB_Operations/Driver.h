#include "training.h"
#ifndef driver_h
#define driver_h
class Driver{
private:
	training* levels;
	int dexterity,tech;
	string name;
public:
	Driver(string name, int dexterity, int tech);
	~Driver();
	training* getLevels();
	int getDexterity();
	int getTech();
	string getName();
	void setDexterity(int offset=1);
	void setTech(int offset=1);
};

Driver::Driver(string name,int dexterity,int tech){
	this->name = name;
	this->dexterity = dexterity;
	this->tech = tech;
	this->levels = (training*)malloc(sizeof(training));
	this->levels->base_level=1;
	memset(levels,0,sizeof(training));
}

Driver::~Driver(){
	free(levels);
}

training* Driver::getLevels(){
	return levels;
}

int Driver::getDexterity(){
	return this->dexterity;
}

string Driver::getName(){
	return this->name;
}

void Driver::setDexterity(int offset){
	this->dexterity += offset;
}

void Driver::setTech(int offset){
	this->tech += offset;
}
#endif