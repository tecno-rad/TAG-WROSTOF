#include <iostream>
#include "Mech.h"
#include "Shop.h"
#include "MechGroup.h"
#define MONEY 150.0
using namespace std;

int main(int argc,char **argv){
	vector<Module> store,shop;
	vector<Module> inventory;
	MechGroup* group = new MechGroup();
	string choose;
	Shop *cinghialeAbbuffato;
	double price;
	vector<Module>::iterator shopIt,inventIt;
	group->setMoney(MONEY);
	store.push_back(*(new Module("Macellomatict47",ARMS,250.0)));
	store.push_back(*(new Module("Flagello2000",ARMS,120.0)));
	store.push_back(*(new Module("MisterMassacro",ARMS,75.0)));
	cinghialeAbbuffato = new Shop("La sosta del cinghiale abbuffato",store);

	cout << "Sintassi dei comandi:\n bn: compra elemento di indice n\n sn: vendi elemento di indice n \n p: stampa inventario\n\n";
	cout << "Benvenuto alla sosta del cinghiale abbuffato!" << "\n\n";
	do{
		int shopidx = 1;
		shop = cinghialeAbbuffato->getProductList();
		cout << "Soldi: " << group->getMoney() << "\n\n";
		shopIt = shop.begin();
		while(shopIt != shop.end()) {
			cout << shopidx << ") " << shopIt->getName() << "$: " << shopIt->getBuyPrice() <<"\n";
			++shopIt;
			shopidx++;
		}
		cout << "\nFai la tua scelta: ";
		cin >> choose;
		if(choose[0]=='b'){
			cout << "Prezzo: " << (price = shop.at(choose[1]-49).getBuyPrice()) << "\n";
			if(group->getMoney()<price) cout << "Impossibile acquistare l'oggetto " 
				<< shop.at(choose[1]-49).getName() << "\n\n";
			else{
				group->setMoney(-price);
				group->addModuleToInventory(shop.at(choose[1]-49));
			}
		}
		else if(choose[0]=='s'){
			vector<Module> tmp = group->getModuleList();
			cout << "Prezzo di vendita: " << (price = tmp.at(choose[1]-49).getSellPrice()) << "\n";
			group->setMoney(price);
			group->removeModuleFromInventory(tmp.at(choose[1]-49));
		}
		else if(choose[0]=='p'){
			int invidx = 1;
			cout << "Inventario:\n";
			vector<Module> tmp = group->getModuleList();
			if(tmp.size()==0) cout << "<VUOTO>\n";
			else{
				inventIt = tmp.begin();
				while(inventIt != tmp.end()) {
					cout << invidx << ") " << inventIt->getName() << "$: " << inventIt->getSellPrice() << "\n";
					++inventIt;
					invidx++;
				}
			}
			cout << "\n";
		}
	}
	while(choose[0]!='e');
	system("PAUSE");
	return 0;
}