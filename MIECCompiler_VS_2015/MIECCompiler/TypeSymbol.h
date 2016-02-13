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
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="name">  TypeSymbol name</param>
	* <param name="type">  Type Object</param>
	*/
	TypeSymbol(std::string name, Type* type) : Symbol(name, type) {}
	/**
	* <summary>  Print  Debugging purpose. </summary>
	*
	* <param name="out">  stream to print on </param>
	*/
	void Print(std::ostream &ost) const {
		Symbol::Print(ost);
	}
	/**
	* <summary>  Destructor Cleanup. </summary>
	*
	*/
	~TypeSymbol() {
		delete mType;
	}
private:

};

#endif