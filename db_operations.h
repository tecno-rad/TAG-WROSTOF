#include <afxdb.h>
#include <afx.h>
#include <odbcinst.h>
#include <string>
#include <stdio.h>
#include "Module.h"
#include "Ability.h"
#include "Shop.h"
using namespace std;
#ifndef db_operations_h
#define db_operations_h
class DBOperations {
private:
        CDatabase cd;
        CRecordset rs;
public:
        DBOperations();
        ~DBOperations();
        Module getModule(string nome);
        Module *getListaModuli();
        Ability getAbility(string nome);
        Ability *getListaAbility();
        Mech getEnemy(string nome);
        Mech *getListaEnemy();
        /**
                DA DEFINIRE
                ricerca per nome? località?
                PER NOME
        **/
        Shop getShop(string nome);
};

DBOperations::DBOperations() {
        LPCTSTR conStr = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\Project\CPP\Prova_DB\Debug\GestioneClienti.mdb;Persist Security Info=False;");
        cd.Open(NULL, false, true, conStr, true);
}

DBOperations::~DBOperations() {
        delete cd;
        delete rs;
}

DBOperations::getModule(std::string nome) {
        string query = "SELECT * FROM Modules Where nome = '" + nome + "'";
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, _T(query), CRecordset::readOnly);
        if(rs.GetRecordCount() == 0)
                return NULL;
        rs.MoveFirst();
        Module modulo;
        CDBVariant varValue;
        rs.GetFieldValue(_T("Code"), varValue);
        int code = varValue.m_lVal;
        rs.GetFieldValue(_T("Bonus"), varValue);
        int bonus = varValue.m_lVal;
        rs.GetFieldValue(_T("Type"), varValue);
        int type = varValue.m_lVal;
        rs.GetFieldValue(_T("Class"), varValue);
        int classMask = varValue.m_lVal;
        rs.GetFieldValue(_T("Description"), varValue);
        string desc = varValue.m_pstring;
        delete rs;
        delete varValue;
        return new Module(code, bonus, type, classMask, nome, desc);
}

DBOperations::getListaModuli(){
        string query = "SELECT * FROM Modules";
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, _T(query), CRecordset::readOnly);
        if(rs.GetRecordCount() == 0)
                return NULL;
        rs.MoveFirst();
        CDBVariant varValue;
        Module *lista = malloc(rs.GetRecordCount() * sizeof(Module));
        for(int i = 0; !rs.IsEOF(); i++) {
                rs.GetFieldValue(_T("Code"), varValue);
                int code = varValue.m_lVal;
                rs.GetFieldValue(_T("Bonus"), varValue);
                int bonus = varValue.m_lVal;
                rs.GetFieldValue(_T("Type"), varValue);
                int type = varValue.m_lVal;
                rs.GetFieldValue(_T("Class"), varValue);
                int classMask = varValue.m_lVal;
                rs.GetFieldValue(_T("Name"), varValue);
                string nome = varValue.m_pstring;
                rs.GetFieldValue(_T("Description"), varValue);
                string desc = varValue.m_pstring;
                lista[i] = new Module(code, bonus, type, classMask, nome, desc);
                rs.MoveNext();
        }
        delete rs;
        delete varValue;
        return lista;
}

DBOperations::getAbility(string nome) {
        string query = "SELECT * FROM Abilities Where nome = '" + nome + "'";
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, _T(query), CRecordset::readOnly);
        if(rs.GetRecordCount() == 0)
                return NULL;
        rs.MoveFirst();
        Ability ability;
        CDBVariant varValue;
        rs.GetFieldValue(_T("Id"), varValue);
        string id = varValue.m_pstring;
        rs.GetFieldValue(_T("Name"), varValue);
        string name = varValue.m_pstring;
        rs.GetFieldValue(_T("Description"), varValue);
        string desc = varValue.m_pstring;
        /**
                DA DISCUTERE
        **/
        rs.GetFieldValue(_T("Effetto"), varValue);
        Effetto effetto = varValue.m_lVal;
        rs.GetFieldValue(_T("Level"), varValue);
        int level = varValue.m_lVal;
        rs.GetFieldValue(_T("Class"), varValue);
        int classMask = varValue.m_lVal;
        rs.GetFieldValue(_T("Delay"), varValue);
        float delay = varValue.m_fltVal;
        delete rs;
        delete varValue;
        return new Ability(id, name, desc, effetto, level, classMask, delay);
}

DBOperations::getListaAbility(){
        string query = "SELECT * FROM Abilities";
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, _T(query), CRecordset::readOnly);
        if(rs.GetRecordCount() == 0)
                return NULL;
        rs.MoveFirst();
        CDBVariant varValue;
        Module *lista = malloc(rs.GetRecordCount() * sizeof(Ability));
        for(int i = 0; !rs.IsEOF(); i++) {
                rs.GetFieldValue(_T("Id"), varValue);
                string id = varValue.m_pstring;
                rs.GetFieldValue(_T("Name"), varValue);
                string name = varValue.m_pstring;
                rs.GetFieldValue(_T("Description"), varValue);
                string desc = varValue.m_pstring;
                /**
                        DA DISCUTERE
                **/
                rs.GetFieldValue(_T("Effetto"), varValue);
                Effetto effetto = varValue.m_lVal;
                rs.GetFieldValue(_T("Level"), varValue);
                int level = varValue.m_lVal;
                rs.GetFieldValue(_T("Class"), varValue);
                int     classMask = varValue.m_lVal;
                rs.GetFieldValue(_T("Delay"), varValue);
                float delay = varValue.m_fltVal;
                lista[i] = new Ability(id, name, desc, effetto, level, classMask, delay);
                rs.MoveNext();
        }
        delete rs;
        delete varValue;
        return lista;
}
#endif