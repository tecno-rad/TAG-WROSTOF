#ifndef _dbOperations_h_included_
#define _dbOperations_h_included_

#include <afxdb.h>
#include <afx.h>
#include <odbcinst.h>
#include <string>
#include <CString>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <sstream>

//#include "Module.h"
//#include "Ability.h"
#include "Shop.h"
#include "Mech.h"
using namespace std;


class DBOperations {

private:
	
	CDatabase *database;
	//CRecordset rs;

	//Converts a CString into a string
	string convertString(CString s);

	//For a shared connection between all methods
	//Opens and returns the connection
	CDatabase *returnDB();

public:

	DBOperations();

	~DBOperations();

	//Returns the pointer to the module with the specified name
	Module* getModule(CString nome);

	//Returns the vector containing all the modules
	vector<Module> getModuleList();

	//Returns the pointer to the Ability with the specified name
	Ability* getAbility(CString nome);

	//Returns the vector containing all the abilities
	vector<Ability> getAbilityList();

	//Returns the pointer to the Mech used by the specified enemy
	Mech* getEnemy(std::string nome);

	//Returns a vector containing all the enemy's Mech
	vector<Mech> getEnemyList();

	//Returns the pointer to the shop with the specified name and type.
	//Type: "Weapon" or "Item"
	//The "Weapon type Shop" will have a list of Modules to sell
	//The "Item type Shop" will have a list of Items to sell
	Shop* getShop(CString nome, std::string type);

	//void saveGame();

	//Game loadGame();

};



DBOperations::DBOperations() {

	database = NULL;
}


DBOperations::~DBOperations() {

}


Module* DBOperations::getModule(CString nome) {

	CDatabase *cd = returnDB();
	CRecordset *rs = new CRecordset(cd);
	try {
		CString query = "SELECT * FROM Modules Where nome = '";
		query.Append(nome);
		CString q_append = "'";
		query.Append(q_append);
	
		rs->Open(CRecordset::forwardOnly, query);
	
		if(rs->GetRecordCount() == 0)
			return NULL;

		Module modulo;
		CDBVariant varValue;

		rs->GetFieldValue(_T("SpeedBonus"), varValue);
		int speedBonus = varValue.m_iVal;
		
		rs->GetFieldValue(_T("ShieldBonus"), varValue);
		int shieldBonus = varValue.m_iVal;

		rs->GetFieldValue(_T("AccuracyBonus"), varValue);
		int accuracyBonus = varValue.m_iVal;

		rs->GetFieldValue(_T("EnergyMaxBonus"), varValue);
		int energyMaxBonus = varValue.m_iVal;

		rs->GetFieldValue(_T("Tipo"), varValue);
		int type = varValue.m_iVal;

		rs->GetFieldValue(_T("Classe"), varValue);
		int classMask = varValue.m_iVal;
		
		//NECESSARIO DEFERENZIARE:
		//se si mantiene il riferimento, al prissimo
		//rs.GetFieldValue cambia anche il valore di DESC
		rs->GetFieldValue(_T("Descrizione"), varValue);
		CString desc = *(varValue.m_pstring);
	
		rs->GetFieldValue(_T("PrezzoVendita"), varValue);
		double vendita = varValue.m_dblVal;

		rs->GetFieldValue(_T("PrezzoAcquisto"), varValue);
		double acquisto = varValue.m_dblVal;

		Module *m = new Module(convertString(nome), 
			type, 
			classMask, 
			convertString(desc), 
			energyMaxBonus, 
			speedBonus, 
			shieldBonus, 
			accuracyBonus);

		m->setBuyPrice(vendita);
		m->setSellPrice(acquisto);

		return m;
	}
	catch(CDBException *e) {
		CString sMessage;
		e->GetErrorMessage(sMessage.GetBufferSetLength(255),255);
		cout << sMessage;
	}

}


vector<Module> DBOperations::getModuleList(){

	try {
		CDatabase *cd = returnDB();
		CRecordset *rs = new CRecordset(cd);

		CString query = "SELECT Nome FROM Modules";
		rs->Open(CRecordset::forwardOnly, query);

		vector<Module> lista;

		if(rs->GetRecordCount() == 0)
			return lista;

		CDBVariant varValue;

		while(!rs->IsEOF()) {

			rs->GetFieldValue(_T("Nome"), varValue);
			CString *nome = varValue.m_pstring;

			lista.push_back(*getModule(*nome));

			rs->MoveNext();
		}

		return lista;
	}
	catch(CDBException *e) {
		CString sMessage;
		e->GetErrorMessage(sMessage.GetBufferSetLength(255),255);
		cout << sMessage;
	}

}


Ability* DBOperations::getAbility(CString nome) {
	try {
		CDatabase *cd = returnDB();
		CRecordset *rs = new CRecordset(cd);
		//cd->Open(NULL, false, true, getConnString(), true);
		//cd.Open(getConnString());

		CString query = "SELECT * FROM Abilities Where nome = '";
		query.Append(nome);
		CString q_append = "'"; //O__O
		query.Append(q_append);
		rs->Open(CRecordset::forwardOnly, query); //, CRecordset::readOnly);

		if(rs->GetRecordCount() == 0)
			return NULL;

		//rs->MoveFirst();
		CDBVariant varValue;

		rs->GetFieldValue(_T("ID"), varValue);
		long id = varValue.m_lVal;
		
		rs->GetFieldValue(_T("Nome"), varValue);
		CString name = *(varValue.m_pstring);

		rs->GetFieldValue(_T("Descrizione"), varValue);
		CString desc = *(varValue.m_pstring);


		CRecordset *rs2 = new CRecordset(cd);
		CString query2 = "SELECT Effects.* FROM Effects, Ability_Effect Where Ability_Effect.IDAbility = "; 
		CString q_append2;
		q_append2.Format("%d", id);
		query2.Append(q_append2);
		CString q_append3 = " AND Ability_Effect.IDEffect = Effects.ID";
		query2.Append(q_append3);
		rs2->Open(CRecordset::forwardOnly, query2); //, CRecordset::readOnly);


		vector<Effect> effetti;
		//rs2->MoveFirst();

		while(!rs2->IsEOF()) {

			rs2->GetFieldValue(_T("Nome"), varValue);
			CString eff_name = *(varValue.m_pstring);

			rs2->GetFieldValue(_T("Target"), varValue);
			CString target = *(varValue.m_pstring);

			rs2->GetFieldValue(_T("IfTarget"), varValue);
			CString if_target = *(varValue.m_pstring);

			rs2->GetFieldValue(_T("IfLauncher"), varValue);
			CString if_launcher = *(varValue.m_pstring);

			rs2->GetFieldValue(_T("Valore"), varValue);
			long valore = varValue.m_lVal;

			rs2->GetFieldValue(_T("Status"), varValue);
			CString status = *(varValue.m_pstring);
		
			effetti.push_back(*(new Effect(convertString(eff_name), convertString(target), valore, convertString(if_launcher), convertString(if_target))));//, *status)));

			rs2->MoveNext();
		}

		rs->GetFieldValue(_T("Livello"), varValue);
		int level = varValue.m_lVal;

		rs->GetFieldValue(_T("Classe"), varValue);
		int classMask = varValue.m_lVal;

		rs->GetFieldValue(_T("Delay"), varValue);
		int delay = varValue.m_iVal;

		rs->GetFieldValue(_T("Tipo"), varValue);
		long type = varValue.m_lVal;

		CString id_str;
		id_str.Format("%d", id);
		return new Ability(convertString(id_str), convertString(name), convertString(desc), effetti, level, classMask, delay, type);
	}
	catch(CDBException *e) {
		CString sMessage;
		e->GetErrorMessage(sMessage.GetBufferSetLength(255),255);
		cout << sMessage;
	}
}


vector<Ability> DBOperations::getAbilityList(){

	try {
		CDatabase *cd = returnDB();
		CRecordset *rs = new CRecordset(cd);
		//cd.Open(NULL, false, true, getConnString(), true);

		CString query = "SELECT * FROM Abilities";
		rs->Open(CRecordset::forwardOnly, query); //, CRecordset::readOnly);

		vector<Ability> lista;
	
		//if there are no abilities, returns the empty vector
		if(rs->GetRecordCount() == 0)
			return lista;

		//rs->MoveFirst();
		CDBVariant varValue;

		while(!rs->IsEOF()) {

			rs->GetFieldValue(_T("Nome"), varValue);
			CString *name = varValue.m_pstring;

			lista.push_back(*getAbility(*name));

			rs->MoveNext();
		}

		return lista;
	}
	catch(CDBException *e) {
		CString sMessage;
		e->GetErrorMessage(sMessage.GetBufferSetLength(255),255);
		cout << sMessage;
	}
}


//
//		Restituisce lo shop specificato dal nome
//		parametri: Nome: nome dello shop (CString)
//				   Type: "Item" o "Weapon" (string)
//
Shop* DBOperations::getShop(CString nome, std::string type) {
 
	try {
		CDatabase *cd = returnDB();
		CRecordset *rs = new CRecordset(cd);

		CString query = "SELECT * FROM Shop_Weapon Where nome = '";
		query.Append(nome);
		CString q_append = "'";
		query.Append(q_append);
	
		//string overloads '==' operator
		if(type == "Item") {
			query = "SELECT * FROM Shop_Item Where nome = '";
			
			//l'append di una stringa costante non funziona
			query.Append(nome);
			CString q_append2 = "'";
			query.Append(q_append2);
		}

		rs->Open(CRecordset::forwardOnly, query);

		if(rs->GetRecordCount() == 0)
			return NULL;


		CDBVariant varValue;

		vector<Module> modules;

		for(int i = 0; !rs->IsEOF(); i++) {
			rs->GetFieldValue(_T("IDModulo"), varValue);
			long id = varValue.m_lVal;

			CRecordset *rs2 = new CRecordset(cd);
			CString query2 = "SELECT * FROM Modules WHERE ID = ";
			CString q_append3;
			q_append3.Format("%d", id);
			query2.Append(q_append3);
			rs2->Open(CRecordset::forwardOnly, query2);

			//NECESSARIO DEFERENZIARE:
			//se si mantiene il riferimento, al prissimo
			//rs.GetFieldValue cambia anche il valore di NAME
			rs2->GetFieldValue(_T("Nome"), varValue);
			CString name = *(varValue.m_pstring);

			Module m = *getModule(name);
			modules.push_back(m);

			rs2->MoveNext();
			rs->MoveNext();
		}

		return new Shop(convertString(nome), modules);	

	}
	catch(CDBException *e) {
		CString sMessage;
		e->GetErrorMessage(sMessage.GetBufferSetLength(255),255);
		cout << sMessage;
	}
}


string DBOperations::convertString(CString s) {
	
	//just a cut and paste from the web, but  it works :)
	CT2CA x(s);
	string ss (x);
	return ss;
	
}



CDatabase* DBOperations::returnDB() {

	//Returns always an open connection to the database
	//if the connection object isn't already inizialized, it inizialize it.
	//if the connection is closed, it opens it.
	//returns the ptr to the object with an open connection
	if(database == NULL)
		database = new CDatabase();
	if(!database->IsOpen())
		database->Open(_T("ODBC;DSN=Robots;"));

	return database;
}

#endif