/**
* @file   SymbolTable.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Symbol Table class
*
*
*/
#ifndef MIEC_SYMBOL_TABLE_H
#define MIEC_SYMBOL_TABLE_H

#include <string>
#include <map>
#include "Symbol.h"
#include "Object.h"

class SymbolTable : public Object {
public:
	
	static SymbolTable* GetInstance() {
		if (!symbolTable_instance){
			symbolTable_instance = new SymbolTable();
		}
		return symbolTable_instance;
	}

	static void Delete() {
		if (symbolTable_instance){
			delete symbolTable_instance;
		}
	}

	bool AddSymbol(Symbol* symbol);
	Symbol* Find(std::string str);
	void Clear();


#ifdef _DEBUG
	void PrintTable() const;
#endif

private:
	SymbolTable();
	SymbolTable(SymbolTable const& obj) = delete;
	void operator=(SymbolTable const& obj) = delete;
	
	// Singleton
	static SymbolTable* symbolTable_instance;
	std::map<std::string, Symbol*> mMap;
};


#endif