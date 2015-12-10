#ifndef MIEC_SYMBOL_H
#define MIEC_SYMBOL_H

#include <string>
#include "Type.h"
#include "Object.h"

class Symbol : public Object {
public:
	std::string GetName() { return mName; }
protected:
	Symbol(std::string name, Type type) : mName(name), mType(type) {}
private:
	std::string mName;
	Type mType;
};



#endif