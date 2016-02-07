/**
* @file   ConstIntSymbol.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Spezialzation of Symbol 
*
*
*/
#ifndef MIEC_CONSTINTSYMBOL_H
#define MIEC_CONSTINTSYMBOL_H

#include "Symbol.h"

class ConstIntSymbol : public Symbol {
public:
	ConstIntSymbol(int value, std::string name, Type* type) : mValue(value), Symbol(name, type){}
	int GetValue() { return mValue; }
private:
	int mValue;
};

#endif