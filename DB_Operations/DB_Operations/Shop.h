#include <string>
#ifndef shop_h
#define shop_h
#include "Module.h"

using namespace std;

class Shop {
private:
        string name;
        vector<Module> products;
public:
        Shop(string nome, vector<Module> products);
        ~Shop();
        vector<Module> getProductList();
        Module getModule(string nome);
};

Shop::Shop(std::string nome, vector<Module> products){
	this->name = name;
	this->products = products;
}

Shop::~Shop(){
	products.~vector();
}

vector<Module> Shop::getProductList(){
	return products;
}

Module Shop::getModule(string nome){
	vector<Module>::iterator it = this->products.begin();
	while(it != this->products.end()){
		if(it->getName() == nome) {
			return *it;
			break;
		}
		++it;
	}
}
#endif