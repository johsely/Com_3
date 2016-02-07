/**
* @file   SymbolFactory.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  SymbolFactory class implementation
*
*
*/
#include "SymbolFactory.h"
#include "SymbolTable.h"
#include "ConstIntSymbol.h"
#include <sstream>

SymbolFactory* SymbolFactory::symbolFactory_instance = NULL;

/**Creates integer symbol*/
Symbol* SymbolFactory::CreateIntegerVariable(size_t &offset, std::string name) {
	size_t integerSize = 2;		
	auto typeSymbol = SymbolTable::GetInstance()->Find("Integer");
	auto symbol = new VarSymbol(offset, name, typeSymbol->GetType());
	offset += integerSize; // add the new offset here
	return symbol;
}
/** creates const int symbol from value */
Symbol* SymbolFactory::CreateConstIntSymbol(int value) {
	auto typeSymbol = SymbolTable::GetInstance()->Find("Integer");
	if (typeSymbol == 0) { return 0; }
	
	std::string name("const");
	name += std::to_string(value);

	auto symbol = new ConstIntSymbol(value, name, typeSymbol->GetType());
	return symbol;
}