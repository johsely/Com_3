#ifndef MIEC_TYPESYMBOL_H
#define MIEC_TYPESYMBOL_H

#include "Symbol.h"

class TypeSymbol : public Symbol {
public:
	TypeSymbol(std::string name, Type type) : Symbol(name, type) {}
private:

};

#endif