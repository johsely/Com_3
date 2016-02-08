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
	virtual ~Symbol() {}
	std::string GetName() { return mName; }
	Type* GetType() { return mType; }
	virtual void Print(std::ostream &ost) const {
		ost << "name: " << mName << " ";
		ost << "size: " << mType->GetSize();		
	};
protected:
	Symbol(std::string name, Type* type) : mName(name), mType(type) {}
	std::string mName;
	Type* mType;
private:
	Symbol();
	
};

#endif