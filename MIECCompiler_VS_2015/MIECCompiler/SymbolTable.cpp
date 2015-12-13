#include "SymbolTable.h"
#include "TypeSymbol.h"
#include "BaseType.h"
#include <string>
#include <iostream>

SymbolTable* SymbolTable::symbolTable_instance = NULL;

SymbolTable::SymbolTable() {	
	// add Integer as type
	Symbol* type = new TypeSymbol("Integer", BaseType(Integer, 2));
	mMap.insert(std::pair<std::string, Symbol*>(type->GetName(), type));
}


bool SymbolTable::AddSymbol(Symbol* symbol){
	return mMap.insert(std::pair<std::string, Symbol*>(symbol->GetName(), symbol)).second;
}

Symbol* SymbolTable::Find(std::string str) {		
	auto iter = mMap.find(str);
	if (iter == mMap.end()){
		return 0;
	}
	return iter->second;
}



void SymbolTable::PrintTable() const{
	for (auto x : mMap) {
		x.second->Print(std::cout);
		std::cout << std::endl;
	}
}