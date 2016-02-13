/**
* @file   VarSymbol.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Varsymbol class
*
*
*/
#ifndef MIEC_VARSYMBOL_H
#define MIEC_VARSYMBOL_H

#include "Symbol.h"

class VarSymbol : public Symbol {
public:
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="offset">  adress ofsett </param>
	* <param name="name">  name of symbol </param>
	* <param name="type">  type object </param>
	*/
	VarSymbol(size_t offset, std::string name, Type* type) : mOffset(offset), Symbol(name, type) {}
	/**
	* <summary>  GetOffset. </summary>
	*/
	size_t GetOffset() { return mOffset; }
	/**
	* <summary>  Print  Debugging purpose. </summary>
	*
	* <param name="out">  stream to print on </param>
	*/
	void Print(std::ostream &ost) const {
		Symbol::Print(ost);
		ost << " offset: " << mOffset;
	}
private:
	size_t mOffset;
};

#endif