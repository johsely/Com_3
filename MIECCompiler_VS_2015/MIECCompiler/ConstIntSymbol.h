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
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="value">   Const value. </param>
	* <param name="name">   name  parsed to Symbol class. </param>
	* <param name="type">   type  parsed to Symbol class. </param>
	*/
	ConstIntSymbol(int value, std::string name, Type* type) : mValue(value), Symbol(name, type){}
	/**
	* <summary>  Getter: access to private mValue. </summary>
	*
	*/
	int GetValue() { return mValue; }
private:
	int mValue;
};

#endif