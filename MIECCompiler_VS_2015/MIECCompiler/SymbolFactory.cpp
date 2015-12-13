#include "SymbolFactory.h"

SymbolFactory* SymbolFactory::symbolFactory_instance = NULL;

Symbol* SymbolFactory::CreateIntegerVariable(size_t &offset, std::string name) {
	size_t integerSize = 2;		
	auto symbol = new VarSymbol(offset, name, BaseType(Integer, integerSize));
	offset += integerSize; // add the new offset here
	return symbol;
}