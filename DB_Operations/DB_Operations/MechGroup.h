#include "Mech.h"
#include "inventory.h"
#ifndef mech_group_h
#define mech_group_h

class MechGroup{
private:
	vector<Mech> members;
	vector<Module> modules;
	double money;
public:
	MechGroup();
	~MechGroup();
	Mech getMember(int number);
	Mech removeMember(int number);
	inventory* getInventory();
	void addModuleToInventory(Module mod);
	void removeModuleFromInventory(Module mod);
	double getMoney();
	void setMoney(double offset);
	vector<Module> getModuleList();
};

MechGroup::MechGroup(){
	this->money=0.0;
}
MechGroup::~MechGroup(){
	
}
void MechGroup::addModuleToInventory(Module mod){
	this->modules.push_back(mod);
}
void MechGroup::removeModuleFromInventory(Module mod){
	vector<Module>::iterator it = modules.begin();
	while(it != modules.end()){
		if(it->getName() == mod.getName()){
			modules.erase(it);
			break;
		}
		++it;
	}
}

double MechGroup::getMoney(){
	return this->money;
}

void MechGroup::setMoney(double offset){
	this->money+=offset;
}

vector<Module> MechGroup::getModuleList(){
	return modules;
}
#endif