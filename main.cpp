#include "db_operations.h"

void printModule();

void printModuleList();

void printShop();

void printAbility();

void printAbilityList();


int main() {

	//printModule();

	//printModuleList();

	printShop();

	//printAbility();

	//printAbilityList();
	

	system("pause");

}


void printAbilityList(){
	
	DBOperations db = *(new DBOperations());

	vector<Ability> list = db.getAbilityList();

	for(int i = 0; i < list.size(); i++) {
	
		cout << "\n\nNome: " << list.at(i).getName() << "\n";
		cout << list.at(i).getDescription() << "\n";
		cout << "Delay: " << list.at(i).getDelay() << "\n";
		cout << "ID: " << list.at(i).getId() << "\n";

		vector<Effect> vect = list.at(i).getEffects();
		for(int j = 0; j < vect.size(); j++) {
	
			cout << "Effect: " << vect.at(j).getName() << "\n";
			cout << "Target: " << vect.at(j).getTarget() << "\n";
			cout << "If_Launcher: " << vect.at(j).getTriggerIfLauncher() << "\n";
			cout << "If_Target: " << vect.at(j).getTriggerIfTarget() << "\n\n";
		}
	
	}
}


 void printAbility() {

	DBOperations db = *(new DBOperations());

    Ability *a = db.getAbility("Inculata Spaziale");
	//Ability *a = db.getAbility("Alabarda Genitale");
	cout << "Nome: " << a->getName() << "\n";
	cout << a->getDescription() << "\n";
	cout << "Delay: " << a->getDelay() << "\n";
	cout << "ID: " << a->getId() << "\n";
	//cout << "Type: " << a->getType() << "\n\n";

	vector<Effect> vect = a->getEffects();
	for(int i = 0; i < vect.size(); i++) {
	
		cout << "Effect: " << vect.at(i).getName() << "\n";
		cout << "Target: " << vect.at(i).getTarget() << "\n";
		cout << "If_Launcher: " << vect.at(i).getTriggerIfLauncher() << "\n";
		cout << "If_Target: " << vect.at(i).getTriggerIfTarget() << "\n\n";
	}

}


void printModule() {
	
	DBOperations db = *(new DBOperations());

	Module *m = db.getModule("First");

	string str = m->getName();
	cout << "Nome " << str << "\n";
	cout << "Desc " << m->getDescription() << "\n";


}


void printModuleList() {

	DBOperations db = *(new DBOperations());

	vector<Module> vect = db.getModuleList();

	for(int i = 0; i < vect.size(); i++) {
		cout << "\n\n";

		Module m = vect.at(i);
		cout << i << "\nNome: " << m.getName() << "\n";
		cout << "Desc: " << m.getDescription() << "\n";
		cout << "BuyPrice: " << m.getBuyPrice() << "\n";
		cout << "SellPrice: " << m.getSellPrice() << "\n";
		cout << "Acc: " << m.getAccuracyBonus() << "\n";
		cout << "EnMax: " << m.getEnergyMaxBonus() << "\n";
		cout << "Shield: " << m.getShieldBonus() << "\n";
		cout << "Speed: " << m.getSpeedBonus() << "\n";
		cout << "Type: " << m.getType() << "\n";
		
	}

}


void printShop() {

	DBOperations db = *(new DBOperations());
	Shop *s = db.getShop("Primo", "1");

	cout << "Nome: ";
	vector<Module> vect = s->getProductList();

	for(int i = 0; i < vect.size(); i++)
		cout << "Modulo: " << vect.at(i).getName() << "\n";
	
	cout << "\n\n";

}