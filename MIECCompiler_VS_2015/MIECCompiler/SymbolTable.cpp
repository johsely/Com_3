#include "SymbolTable.h"
#include "TypeSymbol.h"
#include "BaseType.h"

SymbolTable* SymbolTable::symbolTable_instance = NULL;

SymbolTable::SymbolTable() {
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