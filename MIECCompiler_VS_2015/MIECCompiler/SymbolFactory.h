#ifndef MIEC_SYMBOL_FACTORY_H
#define MIEC_SYMBOL_FACTORY_H

#include <string>
#include "Object.h"
#include "BaseType.h"
#include "VarSymbol.h"

// Singleton for creating Symbols
class SymbolFactory : public Object {
public:
	static SymbolFactory* GetInstance() {
		if (!symbolFactory_instance) {
			symbolFactory_instance = new SymbolFactory();
		}
		return symbolFactory_instance;
	}
	
	static void Delete() {
		if (symbolFactory_instance) {
			delete symbolFactory_instance;
		}
	}

	// offset is added to next level
	Symbol* CreateIntegerVariable(size_t &offset, std::string name);
	Symbol* CreateConstIntSymbol(int value);


private:
	static SymbolFactory* symbolFactory_instance;
};


#endif