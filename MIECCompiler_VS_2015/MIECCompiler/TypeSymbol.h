#ifndef MIEC_TYPESYMBOL_H
#define MIEC_TYPESYMBOL_H

#include "Symbol.h"

class TypeSymbol : public Symbol {
public:
	TypeSymbol(std::string name, Type type) : Symbol(name, type) {}
	void Print(std::ostream &ost) const {
		Symbol::Print(ost);
	}
private:

};

#endif