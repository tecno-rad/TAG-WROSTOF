#include "Ability.h"
#include "Driver.h"
#include "Module.h"
#ifndef mech_h
#define mech_h
Module arms,cockpit,legs;

class Mech{
private:
	Driver *driver;
	int energy,energyMax,shield,speed,accuracy;
	int shieldBonus,speedBonus,accuracyBonus;
	string name;
	unsigned int currentClass; // driver or module??
	vector<Ability> abilities;
	Module cockpit,legs,arms;
public:
	Mech(string name,int energy,int shield,int speed,int accuracy);
	~Mech();
	void setCockpit(Module c);
	void setLegs(Module l);
	void setArms(Module a);
	void addAbility(Ability a);
	void removeAbility(Ability a);
	vector<Ability> getAbilities();
	int getEnergyMax();
	void setEnergyMax(int energyMax);
	int getEnergy();
	void setEnergy(int offset);
	int getShield();
	int getSpeed();
	int getAccuracy();
	string getName();
	// here we return a value that determines status alterations or damage
	int applyAbility(Ability a);
	Driver* getDriver();
	Driver* removeDriver();
	void setDriver(Driver *d);
	Driver* replaceDriver(Driver *d);
};

Mech::Mech(string name,int energyMax,int shield,int speed,int accuracy){
	this->name = name;
	this->energyMax = energyMax;
	this->energy = energyMax;
	this->shield = shield;
	this->speed = speed;
	this->accuracy = accuracy;
	shieldBonus = 0;
	speedBonus = 0;
	accuracyBonus = 0;
	/* HERE WE SHOULD SET A DEFAULT MODULE FOR COCKPIT, LEGS AND ARMS */
	this->legs = legs;
	this->cockpit = cockpit;
	this->arms = arms;
	this->driver = NULL;
}

Mech::~Mech(){
	abilities.~vector();
	/*
	delete cockpit;
	delete legs;
	delete arms;
	*/
}

void Mech::setCockpit(Module c){
	if(c.getType()!=COCKPIT) ; // exception??
	else{
		this->cockpit = c;
		// the cockpit sets bonus for shield
		this->shield -= shieldBonus;
		this->shieldBonus = c.getShieldBonus();
		this->shield += shieldBonus;
	}
}

void Mech::setLegs(Module l){
	if(l.getType()!= LEGS) ; // exception??
	else{
		this->legs = l;
		// the legs sets bonus for speed
		this->speed -= speedBonus;
		this->speedBonus = l.getSpeedBonus();
		this->speed += speedBonus;
	}
}

void Mech::setArms(Module a){
	if(a.getType()!= ARMS) ; // exception??
	else{
		this->arms = a;
		// the legs sets bonus for speed
		this->accuracy -= accuracyBonus;
		this->accuracyBonus = a.getAccuracyBonus();
		this->accuracy += accuracyBonus;
	}
}

void Mech::addAbility(Ability a){
	abilities.push_back(a);
}

void Mech::removeAbility(Ability a){
	vector<Ability>::iterator it = abilities.begin();
	while(it != abilities.end()){
		if(it->getId() == a.getId()) {
			abilities.erase(it);
			break;
		}
		++it;
	}

}

vector<Ability> Mech::getAbilities(){
	return abilities;
}



int Mech::getEnergyMax(){
	return energyMax;
}

void Mech::setEnergyMax(int offset){
	this->energyMax += offset;
}

int Mech::getEnergy(){
	return energy;
}

void Mech::setEnergy(int offset){
	this->energy += offset;
} 

int Mech::getAccuracy(){
	return accuracy;
}

int Mech::getShield(){
	return shield;
}

int Mech::getSpeed(){
	return speed;
}

int Mech::applyAbility(Ability a){
	return 0;
}

Driver* Mech::getDriver(){
	return this->driver;
}

void Mech::setDriver(Driver *d){
	this->driver = d;
}

Driver* Mech::removeDriver(){
	Driver *tmp = this->driver;
	this->driver = NULL;
	return tmp;
}



Driver* Mech::replaceDriver(Driver *d){
	Driver* tmp = this->removeDriver();
	this->setDriver(d);
	return tmp;
}
#endif