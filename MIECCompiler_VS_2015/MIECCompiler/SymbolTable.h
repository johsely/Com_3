/**
* @file   SymbolTable.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Symbol Table class
*
*
*/
#ifndef MIEC_SYMBOL_TABLE_H
#define MIEC_SYMBOL_TABLE_H

#include <string>
#include <map>
#include "Symbol.h"
#include "Object.h"

class SymbolTable : public Object {
public:
	/**
	* <summary>  GetInstance Singleton getter. </summary>
	*
	*/
	static SymbolTable* GetInstance() {
		if (!symbolTable_instance){
			symbolTable_instance = new SymbolTable();
		}
		return symbolTable_instance;
	}
	/**
	* <summary>  Delete. </summary>
	*
	*/
	static void Delete() {
		if (symbolTable_instance){
			delete symbolTable_instance;
		}
	}
	/**
	* <summary>  Addsymbol. </summary>
	*
	* <param name="symbol">  symbol to add </param>
	*/
	bool AddSymbol(Symbol* symbol);
	/**
	* <summary>  Find s symbol in Table by string name. </summary>
	*
	* <param name="str">  name string </param>
	*/
	Symbol* Find(std::string str);
	/**
	* <summary>  Clear Cleanup. </summary>
	*
	*/
	void Clear();


#ifdef _DEBUG
	/**
	* <summary>  PrintTable Debug purpose. </summary>
	*
	*/
	void PrintTable() const;
#endif

private:
	/**
	* <summary>  Constructor. </summary>
	*
	*/
	SymbolTable();
	/**
	* <summary>  Copy Ctor  deleted no implementation. </summary>
	*
	* <param name="obj">  symboltable to copy </param>
	*/
	SymbolTable(SymbolTable const& obj) = delete;
	/**
	* <summary>  Assignment Operator deleted. </summary>
	*
	* <param name="obj">  symboltable to assign</param>
	*/
	void operator=(SymbolTable const& obj) = delete;
	
	// Singleton
	static SymbolTable* symbolTable_instance;
	std::map<std::string, Symbol*> mMap;
};


#endif