/**
* @file   TypeSymbol.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  TypeSymbol Class
*
*
*/
#ifndef MIEC_TYPESYMBOL_H
#define MIEC_TYPESYMBOL_H

#include "Symbol.h"

class TypeSymbol : public Symbol {
public:
	TypeSymbol(std::string name, Type* type) : Symbol(name, type) {}
	void Print(std::ostream &ost) const {
		Symbol::Print(ost);
	}
	~TypeSymbol() {
		delete mType;
	}
private:

};

#endif