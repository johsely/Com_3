/**
* @file   Symbol.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Specialization of IDACEntry and Baseclass for other symbols
*
*
*/
#ifndef MIEC_SYMBOL_H
#define MIEC_SYMBOL_H

#include <string>
#include <ios>
#include "Type.h"
#include "Object.h"
#include "IDACEntry.h"

class Symbol : public IDACEntry {
public:
	/**
	* <summary>  Destructor virtual. </summary>
	*
	*/
	virtual ~Symbol() {}
	/**
	* <summary>  GetName return name of symbol. </summary>
	*
	*/
	std::string GetName() { return mName; }
	/**
	* <summary>  GetType return type of symbol. </summary>
	*
	*/
	Type* GetType() { return mType; }
	/**
	* <summary>  Print  Debugging purpose. </summary>
	*
	* <param name="out">  stream to print on </param>
	*/
	virtual void Print(std::ostream &ost) const {
		ost << "name: " << mName << " ";
		ost << "size: " << mType->GetSize();		
	};
protected:
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="name">  name of Symbol </param>
	* <param name="type">  type of Symbol </param>
	*/
	Symbol(std::string name, Type* type) : mName(name), mType(type) {}
	std::string mName;
	Type* mType;
private:
	/**
	* <summary>  Constructor private. </summary>
	*/
	Symbol();
	
};

#endif