#ifndef MIEC_SYMBOL_H
#define MIEC_SYMBOL_H

#include <string>
#include <ios>
#include "Type.h"
#include "Object.h"

class Symbol : public Object {
public:
	std::string GetName() { return mName; }
	virtual void Print(std::ostream &ost) const {
		ost << "name: " << mName << " ";
		ost << "size: " << mType.GetSize();
	};
protected:
	Symbol(std::string name, Type type) : mName(name), mType(type) {}
	
private:
	Symbol();
	std::string mName;
	Type mType;
};



#endif