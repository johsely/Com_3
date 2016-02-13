/**
* @file   SymbolFactory.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Creation of Symbol Elements
*
*
*/
#ifndef MIEC_SYMBOL_FACTORY_H
#define MIEC_SYMBOL_FACTORY_H

#include <string>
#include "Object.h"
#include "BaseType.h"
#include "VarSymbol.h"

// Singleton for creating Symbols
class SymbolFactory : public Object {
public:
	/**
	* <summary>  GetInstance. Singleton Getter </summary>
	*
	*/
	static SymbolFactory* GetInstance() {
		if (!symbolFactory_instance) {
			symbolFactory_instance = new SymbolFactory();
		}
		return symbolFactory_instance;
	}
	/**
	* <summary>  Delete. </summary>
	*
	*/
	static void Delete() {
		if (symbolFactory_instance) {
			delete symbolFactory_instance;
		}
	}

	/**
	* <summary>  CreateIntegerVariable  Creater, everything added to next level. </summary>
	*
	* <param name="offset">  offset used for adress of variable </param>
	* <param name="name">  name of Symbol </param>
	*/
	Symbol* CreateIntegerVariable(size_t &offset, std::string name);
	/**
	* <summary>  CreateConstIntSymbol. </summary>
	*
	* <param name="value">  constant value int </param>
	*/
	Symbol* CreateConstIntSymbol(int value);


private:
	static SymbolFactory* symbolFactory_instance;
};


#endif